#!/usr/bin/env python

import asyncio
import websockets
import os
import json

NUMBER_OF_THREADS = 5
NUMBER_OF_DATA_BLOCKS = 3
TID = ["A32VG9", "B93OP0", "C91JA7", "D02UI6", "E11PM9"]
t_name = ["", "", "", "", ""]
t_frequency = [0.0, 0.0, 0.0, 0.0, 0.0]
t_iterations = [0, 0, 0, 0, 0]
t_overruns = [0, 0, 0, 0, 0]
t_sum_rt = [0.0, 0.0, 0.0, 0.0, 0.0]
t_data = [["","",""],["","",""],["","",""],["","",""],["","",""]]

async def consumer_handler(websocket) -> None:
    async for message in websocket:
        read_message(message)
        print_data()
        
async def consume(hostname: str, port: int) -> None:
    websocket_resource_url = f"ws://{hostname}:{port}"
    async with websockets.connect(websocket_resource_url) as websocket:
        await consumer_handler(websocket)

def read_message(message: str) -> None:       
    info = json.loads(message)
    thread = 0
    for thread in range (0, NUMBER_OF_THREADS):
        if TID[thread] == info["tid"]:
            break
    t_name[thread] = info["name"]
    t_frequency[thread] = "{:.1f}".format(info["freq"])
    t_iterations[thread] = "{:2d}".format(info["iterations"])
    t_overruns[thread] = "{:3d}".format(info["overruns"])
    t_sum_rt[thread] = "{:.4f}".format(info["sum_rt"][0])
    data = info["data"]
    for d in range(0, NUMBER_OF_DATA_BLOCKS):
        name = data[d]["name"] 
        sum_rt = "{:.4f}".format(data[d]["sum_rt"][0]) 
        max_rt = "{:.4f}".format(data[d]["max_rt"][0])
        avg_rt = "{:.4f}".format(data[d]["avg_rt"][0])
        sum_vs = "{:.4f}".format(data[d]["sum_vs"])
        sum_is = "{:.4f}".format(data[d]["sum_is"]) 
        t_data[thread][d] = name + '  ' + str(sum_rt) + '      ' + str(max_rt) + '      ' + str(avg_rt) + '      ' + str(sum_vs) + '      ' + str(sum_is)
    
def print_data( ) -> None:
    os.system('clear')
    print(' TID     Name     Frequency  Iterations  Overruns   Sum-RT  |                          ' + 
        'Data')
    for thread in range(0, NUMBER_OF_THREADS):
        if not t_name[thread] == "" :
            print(TID[thread] + ' ' + t_name[thread] + '     ' + str(t_frequency[thread]) +
                '         ' + str(t_iterations[thread]) + '         ' + str(t_overruns[thread]) + 
                '     ' + str(t_sum_rt[thread]) + '  |   name   sum_rt[s]  max_rt [s]  avg_rt [ms] ' +
                ' sum_vs [s]  sum_is [s]')
            for data in t_data[thread]:
                print('                                                            | ' + data)
            print('')

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(consume(hostname="localhost", port=5000))
    loop.run_forever()
