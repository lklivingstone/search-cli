## Usage

```
$ ./search-cli --pattern="one" --extensions=c,cpp --threads=10

./a/a3.c: 1

./a/a.c: 2

./b/b3.cpp: 10 11
```

### CLI Help
```
$ ./search-cli --help

Usage:

  ./search_cli --pattern="PATTERN" --extension=cpp,c,py,txt --threads=N

 

Options:

  --pattern     The text or regex to search for (required)

  --extension   Comma-separated file types (choose from: c, cpp, py, txt)

  --threads     Number of parallel threads (required)

  --details     Show thread ID for each file being processed (optional)

  --help        Print this help message

 

Supported file types: c, cpp, py, txt

You may specify any combination and count of these extensions.

Example:

  ./search_cli --pattern="main" --extension=cpp,py --threads=8 --details
```
 
### Detailed Output
```
$ ./search-cli --pattern="one" --extensions=c,cpp --threads=10 --details

=== WATCH THE THREADS MULTY ===

Processing 12 files using 10 threads

Main thread ID: 139745977186112

 

[Thread 139745901647616] Processing: ./thread_pool.cpp

[Thread 139745977181952] Processing: ./utils.cpp

[Thread 139745935218432] Processing: ./a/a3.c

[Thread 139745943611136] Processing: ./a/a2.c

[Thread 139745952003840] Processing: ./main.cpp

[Thread 139745960396544] Processing: ./a/a.c

[Thread 139745968789248] Processing: ./file_search.cpp

[Thread 139745926825728] Processing: ./search_worker.cpp

[Thread 139745910040320] Processing: ./b/b.cpp

[Thread 139745918433024] Processing: ./b/b2.cpp

[Thread 139745935218432] Completed: ./a/a3.c (1 matches)

[Thread 139745943611136] Completed: ./a/a2.c (0 matches)

[Thread 139745935218432] Processing: ./b/b3.cpp

[Thread 139745960396544] Completed: ./a/a.c (1 matches)

[Thread 139745943611136] Processing: ./arg_parser.cpp

[Thread 139745918433024] Completed: ./b/b2.cpp (0 matches)

[Thread 139745910040320] Completed: ./b/b.cpp (0 matches)

[Thread 139745935218432] Completed: ./b/b3.cpp (2 matches)

[Thread 139745901647616] Completed: ./thread_pool.cpp (0 matches)

[Thread 139745977181952] Completed: ./utils.cpp (0 matches)

[Thread 139745968789248] Completed: ./file_search.cpp (0 matches)

[Thread 139745952003840] Completed: ./main.cpp (0 matches)

[Thread 139745926825728] Completed: ./search_worker.cpp (0 matches)

[Thread 139745943611136] Completed: ./arg_parser.cpp (0 matches)

 

===WOW===

./a/a3.c: 1

./a/a.c: 2

./b/b3.cpp: 10 11
```
 
### Invalid Input
```
$ ./search-cli --pattern="one" --extensions=c,cpp --threads=a

Error: Invalid thread count provided. Please provide a valid integer.

Invalid arguments. Use --help for usage.
```
 
### Missing Parameters
```
$ ./search-cli --pattern="one" --extensions=c,cpp

Invalid arguments. Use --help for usage.
```

### No Matches
```
$ ./search-cli --pattern="yoo" --extensions=c,cpp --threads=10

===No game, find something else==='''
```