# Http Header Enumerator
Enumerates HTTP Headers on a list of ip addresses or domain names

Uses libcurl and OpenMP to scan addresses and extract HTTP header information

## Requires
- libcurl4-dev
- build-essential


## Build
```
g++ main.cpp -l curl -fopenmp
```

## Run
```
./a.out iplist.txt NUM_THREADS
```

### Performance
This is a synchronous implementation of an inherently asynchronous process, so it's not exactly rapid :- it'll do about 350000 ips per minute with 12000 threads in an ubuntu VM

If you're trying to scan the entire internet (!) check out [masscan]

[masscan]: <https://github.com/robertdavidgraham/masscan>
