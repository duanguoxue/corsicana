# Corsicana
[![Build Status](https://travis-ci.org/kurt-nj/corsicana.svg?branch=master)](https://travis-ci.org/kurt-nj/corsicana)
[![codecov](https://codecov.io/gh/kurt-nj/corsicana/branch/master/graph/badge.svg)](https://codecov.io/gh/kurt-nj/corsicana)

A header only C++ implementation of the [Aho-Corasick](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm)
algorithm. It aims to be reasonably fast and thread safe.

## Usage

### Trie Construction

Construct a match trie in one of the following manners. New patterns cannot be added to a trie once it is built.
```
corsicana::trie_builder my_trie_builder;
auto my_trie = my_trie_builder.insert("pattern one")
                              .insert("pattern two")
                              .build();
```
```
corsicana::trie_builder my_trie_builder;
auto my_trie = my_trie_builder.insert(container.begin(), container.end()).build();
```
```
corsicana::trie_builder my_trie_builder(container.begin(), container.end());
auto my_trie = my_trie_builder.build();
```
```
corsicana::trie_builder my_trie_builder = { "one", "two", "three" };
auto my_trie = my_trie_builder.build();
```

### Matching

There are a number of different ways to search on a frozen trie

```
auto match = my_trie.match("Input Text");
// get all matches at once
vector<string> all = match.all();
```
```
auto match = my_trie.match("Input Text");
// get the count of matches
int total = match.count();
```
```
auto match = my_trie.match("Input Text");
// return true if we can find any matches
bool any_there = match.any();
```
```
auto match = my_trie.match("Input Text");
// or iterate over them one at a time
for (auto const& m : match) {
    // iteration will search one at a time and can be stopped at any time
}
```

## Testing

Tests are written using [Catch2](https://github.com/catchorg/Catch2) and can be executed by
running `ctest` after building

## Benchmark

A simple benchmark is included the test directory that compares against a simple naive text search.
