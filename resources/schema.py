from dataclasses import dataclass
from typing import List


@dataclass
class Module:
    # module name
    name: str
    
    # sum realtime
    sum_rt: float  # [ms]
        
    # max realtime
    max_rt: float  # [ms]
        
    # average realtime
    avg_rt: float  # [ms]
        
    # sum voluntary context switches
    sum_vs: float
        
    # sum involuntary context switches
    sum_is: float
       
    
@dataclass
class Point:
    # tick
    x: int
        
    # time
    y: float

@dataclass
class ThreadInfo:
    # the thread id
    tid: str
        
    # the thread name
    name: str
        
    # the thread frequency
    freq: float
        
    # amount of iterations
    iterations: int
        
    # amount of detected overruns
    overruns: int
        
    # sum over sumRt
    sum_rt: float  # [ms]
        
    # list about all modules running in the thread
    modules: List[Module]
        
    # graph about the consumed time in the related thread
    graph: List[Point]
