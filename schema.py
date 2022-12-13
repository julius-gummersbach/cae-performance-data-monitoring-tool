from dataclasses import dataclass
from typing import List

@dataclass
class ThreadData:
  name: str
  sum_rt: float # [s]
  max_rt: float # [s]
  avg_rt: float # [ms]
  sum_vs: float # [s]
  sum_is: float # [s]
    
    
@dataclass
class ThreadInfo:
  tid: str
  name: str
  freq: float
  interations: int
  overruns: int
  sum_rt: float     # [s]
  data: List[ThreadData]
