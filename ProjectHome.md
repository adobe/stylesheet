# Style sheet handling library #

## Description ##
This portable C++ library implements a Generic Style Sheet syntax parser with CSS syntax (see http://en.wikipedia.org/wiki/CSS) without predefined HTML/CSS properties, types or semantic.
There is only the syntax parser allowing for a user defined semantics (see http://en.wikipedia.org/wiki/Style_sheet_language).

## Features ##
  * style sheet document parsing and extraction of properties' values;
  * style sheet document merge with inline properties.

## Intended use ##
Separate the structure of objects from the description of each object.
If you have a document structure in whatever language (for example XML) and you want to keep some properties separated from the structure definition you can use this library to specify properties for your objects.

## What it does not ##
The library does not define properties for HTML (text-color, border-style, ...).

### Examples ###
document describing objects (in XML format):
```
<doc>
  <room id="myroom">
    <chair id="chair1" class="plastic" />
    <chair id="chair2" class="wood" style="hidden: true;" />
  </room>
</doc>
```
document describing object properties using a style sheet with CSS syntax:
```
#myroom { light: top white; }
.plastic { transparency: 50%; }
.wood { color: brown; }
```

## Syntax ##
The syntax is the same as defined by CSS2 standard.
```
selector { property-name: property-value; }
```

## Current limitations ##
  * Only one selector is allowed; it is not possible to use the following syntax:
```
selector [, selector, ...] { property-name: property-value; }
```
  * Comments are not allowed yet

## Implementation ##
The library is composed by a set of C++ classes.

The library is not platform-dependent.

## Dependencies ##
This library uses the following open source libraries
  * [boost Tokenizer Library](http://www.boost.org/doc/libs/1_42_0/libs/tokenizer/index.html) (header only);
  * [Boost String Algorithms Library](http://www.boost.org/doc/libs/1_42_0/doc/html/string_algo.html) (header only).