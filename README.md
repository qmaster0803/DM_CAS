## Discrete Mathematics Computer Algebra System
### Main idea
**Discrete Computer Algebra System (DM_CAS)** - is ETU DM&TI course project, aimed at creating a computer algebra system that is capable of performing the simplest operations on: natural, integer, rational numbers, as well as polynomials.
For Natural, Integer, Rational and Polynomial data types own classes have been created, UI written using the **ncourses** library.
P.S. The program has been tested only on Ubuntu and Debian distributions, so use linux :)

![Interface](https://github.com/user-attachments/assets/145f8e8a-88c8-4d01-8720-bb420d0559f6)

---
### Build from source
#### 1. Building:
##### Install dependencies:
```
sudo apt install build-essential cmake libncurses-dev libgtest-dev
```
Execute following command in project root directory to build project:
```
bash ./build.sh
```
#### 2. Run all tests
```
cd build && ctest
```

#### 2. Execute:
To exectute builded binary, you need to write following in terminal:
```
./build/DM_CAS
```
---
### Help
So, you execute the program, now you have a lot of questions. Lets take it in order:
#### Interface:
- In line with "->" you can **write operations**, which you want to calculate. In line "=" you can **see calculated result**;
- **F3** - to enable/disable autoscroll;
- **F4** - by default, all numbers interpreted as Natural, to switch calculation mode you need to press **F4** key. So program have only four calculation modes: Natural, Integer, Rational, Polynomial. To use another data type without switch between modes, you need to add suffix: n - for Natural, i - for Integer, r - for Rational, p - for Polynomial;
- **F5** and **F6** - to scroll help message;
- To scroll in main area you need to use **Page Up** and **Page Down** buttons;
- Also you can **scroll by results and expressions** by pressing **Up arrow** and **Down arrow** keys on keyboard.
- To exit from program you need to press **Ctrl + C** hotkey.
- Examples of writing types:
  - Natural: 1, 0, 2342, 43n;
  - Integer: -1098, 0, 213125, 12i;
  - Rational: -12/13, -15/-13, 23/-5, 5.6, 0.10, 0/5, 23, -5, 90/34r;
  - Polynomial: 1, 5, {5/3^3;1^0} (for polynomial like: (5/3)x^3 + 1), {56^2;1}p.
#### Available commands:
So, you can use operations from [this table](https://docs.google.com/document/d/1Dv_6AIhxg_3ezu6VMcEnMpyfRzgym9l8PmE4ULGfjgM/edit?tab=t.0) with given arguments in format like this: [\<NAME\>\_\<ARG\_TYPES\>\_\<RET_TYPE\>] \<ARGS\>. Alternative names with human-readable names are presented below:

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
| inverse | Rational | [inverse] a |
| simple\_roots | Polynomial | [simple\_roots] a |

| Functions with two arguments | Compatible types | Example |
| ---------------------------- | ---------------- | ------- |
| cmp | Natural, Integer, Rational | [cmp] a b |
| gcd | Natural, Integer, Polynomial | [gcd] a b |
| lcm | Natural, Integer | [lcm] a b |
