# Single_Producer_Single_Consumer_Bounded_Queue
Last Benchmark Results:


<pre>
2023-06-20T18:26:30+00:00
Running ./SpscBenchmark
Run on (8 X 2894.56 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 8192 KiB (x1)
Load Average: 0.24, 0.11, 0.03
***WARNING*** Library was built as DEBUG. Timings may be affected.
---------------------------------------------------------------------------
Benchmark                                 Time             CPU   Iterations
---------------------------------------------------------------------------
Spsc_Bench_spsc_simulate/1            49193 ns        39173 ns        17939
Spsc_Bench_spsc_simulate/2            49927 ns        40290 ns        17971
Spsc_Bench_spsc_simulate/4            49769 ns        39750 ns        17385
Spsc_Bench_spsc_simulate/8            48960 ns        38662 ns        17691
Spsc_Bench_spsc_simulate/16           49950 ns        40042 ns        18148
Spsc_Bench_spsc_simulate/32           51166 ns        41029 ns        16749
Spsc_Bench_spsc_simulate/64           48961 ns        39367 ns        17790
Spsc_Bench_spsc_simulate/128          50684 ns        41142 ns        16696
Spsc_Bench_spsc_simulate/256          49754 ns        39508 ns        17449
Spsc_Bench_spsc_simulate/512          51388 ns        39617 ns        17022
Spsc_Bench_spsc_simulate/1024         64922 ns        42557 ns        16218
Spsc_Bench_spsc_simulate/2048        108691 ns        44641 ns        15954
Spsc_Bench_spsc_simulate/4096        198816 ns        50822 ns        10000
Spsc_Bench_spsc_simulate/8192        390161 ns        58212 ns        11497
Spsc_Bench_spsc_simulate/16384       744142 ns        67367 ns        10031
Spsc_Bench_spsc_simulate/32768      1416746 ns        78597 ns         8437
Spsc_Bench_spsc_simulate/65536      2716113 ns        83225 ns         1000
Spsc_Bench_spsc_simulate/131072     5761805 ns       126903 ns         1000
Spsc_Bench_spsc_simulate/262144    11053261 ns       154529 ns         1000
Spsc_Bench_spsc_simulate/524288    21549470 ns       211756 ns         1000
Spsc_Bench_spsc_simulate/1048576   43041637 ns       186342 ns          100
</pre>
