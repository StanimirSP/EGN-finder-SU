# EGN finder for Sofia University

Finds the Unique citizenship number (Bulgarian: ЕГН/EGN) of any Sofia University student given their faculty number.

The script abuses the information webpage https://cas.uni-sofia.bg/index.php.

As this is now public, the university may soon fix this exploit by removing the page,
or by adding rate limits or by some other way. Once that happens, it is very unlikely
that I will try to provide fixes.

## Building
Clone the repository and compile both cpp programs (with the appropriate names for the executables), e.g.
```
git clone https://github.com/StanimirSP/EGN-finder-SU
cd EGN-finder-SU
g++ -O3 -std=c++20 EGN_generator/*.cpp -o egn_generator
g++ -O3 -std=c++20 EGN_sort/*.cpp -o egn_sort
```

## Usage
```
./find_EGN.sh <fn> <gender: {m,f}> <birthdate range start> [<birthdate range end>]
```
For example
```
# this may take a significant amount of time depending on the number of possible EGNs it needs to check
# though it finds it in couple of minutes for 1-year birthday range (if it is correct)
# if you want to add restrictions on the penultimate 3 digits (you may want this if you know the birth city of the student),
# you can use CBEGIN and CEND environment variables
# this makes the search much faster in most cases

./find_EGN.sh 62285 m 19990101 19991231
# output: 62285, sspetrov1 -> 9902167526
```


## Disclaimer
This project was created only for fun and for educational purposes.

I don't know (and I don't care) whether its use is legal or not.

Do not use for malicious purposes (if there can be any).
