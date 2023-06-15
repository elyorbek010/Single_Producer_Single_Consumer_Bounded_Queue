# Single_Producer_Single_Consumer_Bounded_Queue
Last Benchmark Results:


<pre>
2023-06-15T08:23:19+00:00
Running ./SpscBenchmark
Run on (12 X 2894.56 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 512 KiB (x12)
  L3 Unified 8192 KiB (x1)
Load Average: 0.61, 0.36, 0.14
***WARNING*** Library was built as DEBUG. Timings may be affected.
---------------------------------------------------------------------------
Benchmark                                 Time             CPU   Iterations
---------------------------------------------------------------------------
Spsc_Bench_spsc_simulate/1            97773 ns        74985 ns         9605
Spsc_Bench_spsc_simulate/2            99486 ns        75591 ns         9691
Spsc_Bench_spsc_simulate/4            96996 ns        73227 ns         9038
Spsc_Bench_spsc_simulate/8            99182 ns        75848 ns         9336
Spsc_Bench_spsc_simulate/16           96832 ns        74265 ns         9335
Spsc_Bench_spsc_simulate/32           95561 ns        71932 ns         9523
Spsc_Bench_spsc_simulate/64           96827 ns        74207 ns         9823
Spsc_Bench_spsc_simulate/128          94713 ns        72721 ns         9834
Spsc_Bench_spsc_simulate/256          97474 ns        72667 ns         9610
Spsc_Bench_spsc_simulate/512         106376 ns        76416 ns         8680
Spsc_Bench_spsc_simulate/1024        123900 ns        77739 ns         8604
Spsc_Bench_spsc_simulate/2048        241447 ns       113442 ns         6314
Spsc_Bench_spsc_simulate/4096        373905 ns       116400 ns         5957
Spsc_Bench_spsc_simulate/8192        671160 ns       119924 ns         5512
Spsc_Bench_spsc_simulate/16384       836891 ns        87161 ns         6823
Spsc_Bench_spsc_simulate/32768      1587482 ns       101107 ns         6760
Spsc_Bench_spsc_simulate/65536      3142882 ns       128256 ns         1000
Spsc_Bench_spsc_simulate/131072     6150440 ns       152917 ns         1000
Spsc_Bench_spsc_simulate/262144    11862611 ns       161467 ns         1000
Spsc_Bench_spsc_simulate/524288    25133426 ns       173680 ns          100
Spsc_Bench_spsc_simulate/1048576   44749236 ns       192306 ns          100
</pre>
