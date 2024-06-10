## 1-2

**In a 64-bit system using 4KB pages, which bits are used to represent the page offset, and which are used to represent the page number?**

**How about for a 64-bit system using 2MB pages? Which bits are used for page number and which are for page offset?**

**In a 2GB buffer, how many 2MB hugepages are there?**

## 2-2

**Include the bitflip observation statistics in the table below. Then answer the following questions:**

**Do your results match your expectations? Why might some attacker pairings result in more flips than others? Do you expect any of the pairs to never cause a flip?**

| Hammering Pairs                  | A/B | A/C | A/D |
| -------------------------------- | --- | --- | --- |
| Number of Successes (100 trials) |     |     |     |


## 3-1

**Given a victim address `0x752C3000`, what is the value of its \<Row id\>? The value of its \<Column id\>?**

**For this same victim address, when the exact XOR function being used for computing the \<Bank id\> is unknown, list all possible attacker addresses that stays in the row below the victim address (i.e., the attacker's \<Row id\> is 1 more than the victim's) while sharing the same \<Column id\> and \<Bank id\> Hint: there should be 16 such addresses total.**


## 3-2

**Write a short code snippet (psuedocode) to implement a program that takes two addresses addr_A and addr_B as input and outputs a boolean value to indicate whether they map to the same bank or not. The style of your psuedocode can either be C-style, or can follow the single-sided Rowhammer assembly code example from the lecture slides:**

```asm
loop:
mov (A), %eax
mov (A_dummy), %ecx
clflush (A)
clflush (A_dummy)
mfence
jmp loop
```


## 3-3

**Based on the XOR function described in the lab handout, determine which of the 16 candidate addresses you derived in Discussion Question 3-1 maps to the same bank.**


## 3-5 (Optional)

**Report the statistics produced by your code when running part3, and describe how you can use the difference in these statistics to distinguish between the pairs.**


## 4-1


**Given the ECC type descriptions listed above, fill in the following table (assuming a data length of 4).**


|   | 1-Repetition (No ECC) | 2-Repetition | 3-Repetition | Single Parity Bit | Hamming(7,4) |
| - | --------------------- | ------------ | ------------ | ----------------- | ------------ |
| **Code Rate (Data Bits / Total Bits)** | 1.0 | | | | |
| **Max Number of Errors Can Detect**    |   1 | | | | |
| **Max Number of Errors Can Correct**   |   0 | | | | |



## 4-3

**When a single bit flip is detected, describe what action should be conducted to correct this error with Hamming(22,16).**


## 4-5

**Can the Hamming(22,16) code we implemented always protect us from rowhammer attacks? If not, describe how a clever attacker could work around this scheme.**

