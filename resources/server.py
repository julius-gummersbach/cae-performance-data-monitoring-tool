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
parser.add_argument("-min", "--minValue", action="store", default=int(62))  # one second
parser.add_argument("-max", "--maxValue", action="store", default=int(258492))  # 3 sid. days
parser.add_argument("-f", "--Frequency", action="store", default=float(62.5))
parser.add_argument("-i", "--Iteration", action="store", default=int(5))
args = parser.parse_args()

DATA_COUNT = random.randint(int(args.minValue), int(args.maxValue) + 1)
NUMBER_OF_THREADS = 5
NUMBER_OF_DATA_BLOCKS = 3
TID = ["A32VG9", "B93OP0", "C91JA7", "D02UI6", "E11PM9"]
T_NAME = ["Thread01", "Thread02", "Thread03", "Thread04", "Thread05"]
T_FREQUENCY = args.Frequency
T_ITERATIONS = args.Iteration


@dataclass_json
@dataclass
class CThreadData:  # equals Module
    name: str
    sum_rt: float  # [s]
    max_rt: float  # [ms]
    avg_rt: float  # [ms]
    sum_vs: float
    sum_is: float  # [s]


@dataclass_json
@dataclass
class CThreadInfo:
    tid: str
    name: str
    freq: float
    iterations: int
    overruns: int
    sum_rt: float  # [s]
    data: List[CThreadData]
    graph: List[tuple[int, float]]


def calc_data(thread):
    iterations = T_ITERATIONS
    normal_runtime = 1000.0 / T_FREQUENCY
    name = T_NAME[thread]
    sum_rt = 0.0
    max_rt = 0.0
    sum_vs = 0.0
    sum_is = 0.0
    avg_rt = (sum_rt * 1000.0) / iterations
    data = CThreadData(name, sum_rt, max_rt, avg_rt, sum_vs, sum_is)
    return data


def fill_data(thread):
    tid = TID[thread]
    name = T_NAME[thread]
    freq = T_FREQUENCY
    iterations = T_ITERATIONS
    overruns = 0
    sum_rt = 0
    data = []
    graph: list[tuple[int, float]] = []

    expected_val = random.uniform(8, 12)
    for i in range(0, DATA_COUNT):
        y: float = abs(random.normal(expected_val, expected_val / 4, 1)[0])
        x = i * iterations
        graph.append((x, y))
        sum_rt += y
        data.append(calc_data(thread))

    info = CThreadInfo(tid, name, freq, iterations, overruns, sum_rt, data, graph)
    return info


async def send_info(websocket, path):
    for i in range(NUMBER_OF_THREADS):
        info = fill_data(i)
        await websocket.send(info.to_json())
        await asyncio.sleep(0.2)


start_server = websockets.serve(send_info, 'localhost', 5000)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()

