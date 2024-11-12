## Discrete Mathematics Computer Algebra System
### Main idea
Discrete Computer Algebra System (DM_CAS) - is ETU DM&TI course project, aimed at creating a computer algebra system that is capable of performing the simplest operations on: natural, integers, rational numbers, as well as polynomials.
For Natural, Integer, Rational and Polynomial own classes have been created, UI written using the **ncourses** library.

### Build
#### 1. Building:
Execute following command in project root directory to build:
```
sudo bash ./build.sh
```
#### 2. Execute:
```
./build/DM_CAS
```

### Help
So, you execute the program, now you have a lot of questions. Lets take it in order:
#### Interface:
- In line with "->" you can **write operations**, which you want to calculate. In line "=" you can **see calculated result**;
- **F3** - to enable autoscroll;
- **F4** - by default, all nums interpreted as Natural, to switch calculation mode you need to press **F4** key. To use another data type, different from mode type, you need to add prefix: n - for Natural, i - for Integer, r - for Rational, p - for Polynomial;
- **F5** and **F6** - to scroll help message;
- Also you can **scroll by results** and expressions by pressing **up** and **down arrows** on keyboard.
#### Available commands:
So, you can use operations from [this table](https://docs.google.com/document/d/1Dv_6AIhxg_3ezu6VMcEnMpyfRzgym9l8PmE4ULGfjgM/edit?tab=t.0) with given arguments like: [\<NAME\>\_\<ARG\_TYPES\>\_\<RET_TYPE\>] \<ARGS\>. Another operations listed below:

| Operation | Compatible types | Example |
| --------- | ---------------- | ------- |
| Increment | Natural, Integer | a ++ |
| Decrement | Natural, Integer | a -- |
| Derivative | Polynomial | {a^k;b^n} ' |
| Addition | All types | a + b |
| Substraction | All types | a - b |
| Multiplication | All types (also you can multiply polynomial on rational number) | a * b |
| Shift | Natural, Integer, Polynomial (mul by x^k) | a << k (k - Natural) |
| Div | All types | a / b |
| Mod | Natural, Integer, Polynomial | a % b |

| Functions with one argument | Compatible types | Example |
| --------- | ---------------- | ------- |
| is_zero   | All types        | [is_zero] a |
| abs       | Integer, Rational | [abs] a |
| is_pos    | Integer, Rational | [is_pos] a |
| neg - multiply on -1 | Integer, Rational | [neg] a |
| Nat - try cast to Natural | Integer, Rational | [Nat] a |
| Int - try cast to Integer | Natural, Rational | [Int] a |
| Rat - cast to Rational | Natural, Integer | [Rat] a |
| Pol - cast to Polynomial | Natural, Integer, Rational | [Pol] a |
| is\_int - check for an Integer | Rational, Polynomial | [in\_int] a |
| msc - most significant coefficient | Polynomial | [msc] a |
| deg - degree of Polynomial | Polynomial | [deg] a |
| fac | Polynomial | [fac] a |
| simple\_roots | Polynomial | [simple\_roots] a |

| Functions with two arguments | Compatible types | Example |
| ---------------------------- | ---------------- | ------- |
| cmp | Natural, Integer, Rational | [cmp] a b |
| gcd | Natural, Integer, Polynomial | [gcd] a b |
| lcm | Natural, Integer | [lcm] a b |
