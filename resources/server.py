#!/usr/bin/env python

import asyncio
import websockets
import argparse
from dataclasses_json import dataclass_json
from dataclasses import dataclass
from typing import List
from numpy import random

parser = argparse.ArgumentParser(
    prog='Script to simulate a server',
    description='Generate a JSON-File per Thread',
    epilog='Created JSON-Files script ended')
# At least 9 values are needed for the graph to render
parser.add_argument("-min", "--minValue", action="store", default=int(16))  # 62 = one second
parser.add_argument("-max", "--maxValue", action="store", default=int(32))  # 258492 = 3 sid. days
parser.add_argument("-f", "--Frequency", action="store", default=float(62.5))
parser.add_argument("-i", "--Iteration", action="store", default=int(5))   # 5
args = parser.parse_args()

DATA_COUNT = random.randint(int(args.minValue), int(args.maxValue) + 1)
NUMBER_OF_THREADS = 5
NUMBER_OF_DATA_BLOCKS = 3
TID = ["A32VG9", "B93OP0", "C91JA7", "D02UI6", "E11PM9"]
T_NAME = ["Thread01", "Thread02", "Thread03", "Thread04", "Thread05"]
MODULE_NAME = ["Weather", "Light", "Aerodynamics", "Trees", "Clouds", "Water", "Cockpit", "Airstream",
               "Sound", "Bandits", "Fuel", "Damages"]
T_FREQUENCY = args.Frequency
T_ITERATIONS = args.Iteration


@dataclass_json
@dataclass
class Module:
    name: str
    sum_rt: float  # [s]
    max_rt: float  # [ms]
    avg_rt: float  # [ms]
    sum_vs: float
    sum_is: float  # [s]


@dataclass
class Point:
    x: int      # tick (16ms)
    y: float    # time (ms)


@dataclass_json
@dataclass
class CThreadInfo:
    tid: str
    name: str
    freq: float
    iterations: int
    overruns: int
    sum_rt: float  # [s]
    modules: List[Module]
    graph: List[Point]
    isDone: bool


# Calculates Module info for one singular module
def calc_data(total_runtime, module_index):
    iterations = T_ITERATIONS
    name = MODULE_NAME[module_index]
    # sum_rt minimum runtime: Time for one run in ms (1000 / T_Frequency) * number of iterations
    sum_rt = round(total_runtime, 2)
    avg_rt = round(sum_rt / iterations, 2)
    max_rt = round(random.uniform(avg_rt, sum_rt), 2)
    sum_vs = random.randint(0, 100)
    sum_is = random.randint(0, 100)
    data = Module(name, sum_rt, max_rt, avg_rt, sum_vs, sum_is)
    return data


def fill_data(thread, last):
    tid = TID[thread]
    name = T_NAME[thread]
    freq = T_FREQUENCY
    iterations = T_ITERATIONS
    overruns = random.randint(0, iterations)
    sum_rt = 0
    modules = []
    graph: list[Point] = []

    expected_val = random.uniform(8, 12)
    for i in range(0, DATA_COUNT):
        y: float = abs(random.normal(expected_val, expected_val / 4, 1)[0])
        x = i * iterations
        graph.append(Point(x, y))
        sum_rt += y
    sum_rt = round(sum_rt, 2)
    # Adding Module info
    module_count = random.randint(3, 12)
    temp = sum_rt
    modules_left = module_count
    for k in range(0, module_count):
        if k != module_count - 1:
            mu = temp / modules_left
            module_sum_rt = round(random.uniform(mu * 1/2, mu * 3/2), 2)
            temp -= module_sum_rt
            modules_left -= 1
            modules.append(calc_data(module_sum_rt, k))
        else:
            modules.append(calc_data(temp, k))
    info = CThreadInfo(tid, name, freq, iterations, overruns, sum_rt, modules, graph, last)
    return info


async def send_info(websocket, path):
    print("Sending a message each for " + str(NUMBER_OF_THREADS) + " threads...")
    for i in range(NUMBER_OF_THREADS):
        if i != (NUMBER_OF_THREADS - 1):
            info = fill_data(i, False)
        else:
            info = fill_data(i, True)
        print("Thread " + str(i+1))
        print(info.to_json())
        print()
        await websocket.send(info.to_json())
        await asyncio.sleep(0.2)


start_server = websockets.serve(send_info, 'localhost', 5000)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

