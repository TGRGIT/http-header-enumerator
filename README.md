# Http Header Enumerator
Enumerates HTTP Headers on a list of ip addresses

Uses libcurl and OpenMP to scan ip addresses and extract HTTP header information

## Requires
- libcurl4-dev
- build-essential


## build
```
g++ main.cpp -l curl -fopenmp
```

## run
```
./a.out iplist.txt 1024
```

### Performance
This is a synchronous implementation of an inherently asynchronous process, so it's not exactly rapid :- it'll do about 350000 ips per minute with 12000 threads in an ubuntu VM

If you're trying to scan the entire internet (!) check out [masscan]

[masscan]: <https://github.com/robertdavidgraham/masscan>
