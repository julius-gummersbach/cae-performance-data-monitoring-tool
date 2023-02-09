#!/usr/bin/env python

import asyncio
import websockets
import json
from dataclasses_json import dataclass_json
from dataclasses import dataclass
from typing import List
from numpy import random

NUMBER_OF_THREADS = 5
NUMBER_OF_DATA_BLOCKS = 3
TID = ["A32VG9", "B93OP0", "C91JA7", "D02UI6", "E11PM9"]
T_NAME = ["Thread01", "Thread02", "Thread03", "Thread04", "Thread05"]
T_FREQUENCY = [60.0, 30.0, 60.0, 15.0, 30.0]
T_ITERATIONS = [5, 9, 4, 16, 8]


@dataclass_json
@dataclass
class CThreadData:
    name: str
    sum_rt: float  # [s]
    max_rt: float  # [s]
    avg_rt: float  # [ms]
    sum_vs: float  # [s]
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


def calc_data(thread):
    iterations = T_ITERATIONS[thread]
    normal_runtime = 1000.0 / T_FREQUENCY[thread]
    name = T_NAME[thread]
    sum_rt = 0.0
    max_rt = 0.0
    sum_vs = 0.0
    sum_is = 0.0
    for i in range(0, iterations):
        runtime = random.normal(normal_runtime, 2.0, 1)
        sum_rt = sum_rt + (runtime / 1000.0)
        if runtime > (max_rt * 1000.0):
            max_rt = (runtime / 1000.)
        sum_vs = sum_vs + (0.1 / iterations)
        sum_is = sum_is + (0.25 / iterations)
    avg_rt = (sum_rt * 1000.0) / iterations
    data = CThreadData(name, sum_rt, max_rt, avg_rt, sum_vs, sum_is)
    return data


def fill_data(thread):
    tid = TID[thread]
    name = T_NAME[thread]
    freq = T_FREQUENCY[thread]
    iterations = T_ITERATIONS[thread]
    overruns = 0
    sum_rt = 0
    data = []
    for i in range(NUMBER_OF_DATA_BLOCKS):
        tmp_data = calc_data(thread)
        sum_rt = sum_rt + tmp_data.sum_rt
        data.append(tmp_data)

    info = CThreadInfo(tid, name, freq, iterations, overruns, sum_rt, data)
    return info


async def send_info(websocket, path):
    thread_number = 0
    while True:
        info = fill_data(thread_number)
        await websocket.send(info.to_json())
        thread_number = thread_number + 1
        if thread_number >= NUMBER_OF_THREADS:
            thread_number = 0
        await asyncio.sleep(0.2)


start_server = websockets.serve(send_info, 'localhost', 5000)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
