# MIT Secure Hardware Design Spring 2023
Welcome to the course starter code for MIT's Secure Hardware Design class!

This repository contains the starter code provided to students for each of our labs. This README contains instructions for how to run the labs on your own machines and is intended for use by individuals looking to self-study our materials (or instructors looking to use our materials as part of their course curriculum).

You can reach out to our team at `hw-sec-lab-dev` at `mit.edu`.

Our course website can be found [here](http://csg.csail.mit.edu/6.888Yan/).

This repository is a companion document to our lab handouts which can be found [here](http://csg.csail.mit.edu/6.888Yan/labs).

# Want to use this in your course?
Please contact `hw-sec-lab-dev` at `mit.edu` before using any of our material in your course. We can provide you with the instructor solutions, sample gradebook, and grading scripts.

## Licensing
This code is released under the MIT license.

```
MIT License

Copyright (c) 2022 Mengjia Yan, Joseph Ravichandran, Peter Deutsch,
                   Weon Taek Na, Jack Cook, Miles Dai, Miguel Gomez-Garcia

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

Additionally:

```
Use of MIT Name
"MIT", "Massachusetts Institute of Technology", and its logos and seal
are trademarks of the Massachusetts Institute of Technology. Except for
purposes of attribution as required by our Creative Commons License, you
may not use MIT's names or logos, or any variations thereof, without
prior written consent of MIT. You may not use the MIT name in any of its
forms nor MIT seals or logos for promotional purposes, or in any way that
deliberately or inadvertently claims, suggests, or in MIT's sole judgment
gives the appearance or impression of a relationship with or endorsement
by MIT.
```

# Target Audience
We know that not every student who takes our course will pursue hardware security research as a career. In fact, it is likely many of them will never need to develop another microarchitectural attack again after this course.

For that reason, we want to ensure students learn not only how to implement cutting edge hardware attacks, but also understand how to reason about hardware security as an aspect of secure systems design and defense in depth.

These lab experiments provide the depth aspect of the course, where students implement full end to end microarchitectural attacks against real world processors. We encourage instructors who implement these labs in their course to encourage critical discussion of how to reason about these attacks in practice after allowing students to complete the exercises. We have found these labs provide a great jumping point leading to rich classroom discussions.

## Lab Descriptions

Here's a description of what to expect from each lab in this repository. Our lab content provides both a good deal of depth into what we think are the most important problems for architects to pay attention to, as well as a good deal of breadth to get students exposed to a variety of elements of secure hardware design.

# Lab 1- Cache Side Channels

**Learning Objectives**
* Discover L1/ L2/ L3 caches in practice and how they are shared in modern multicore systems.
* Explore eviction set construction and how to differentiate access latencies across the memory hierarchy.
* Implement the `prime+probe` technique to construct a covert channel.
* Build an adversary to reveal a secret from a victim process.

**Description**
This lab is a deep introduction to the problem of microarchitectural security. In this lab, students will learn how to reverse engineer an unfamiliar memory system, build a covert channel, and reveal a secret from a victim process.

**Setup**
For this lab, we granted each student their own SMT physical core (so, two logical cores) on a shared server. The TA maintained a list of which student owns which cores as part of the student information database, and a script was used to automatically email every student their assigned cores (as well as their login information).

Students were asked to fill in the `cpu.mk` file with their given cores (and we relied on a mix of the honor system and careful TA supervision to ensure that students did not maliciously attack other students).

We deployed this lab on a 96-core server. This lab could be done using any bare metal Intel machine (such as a Google Cloud Platform N2 instance).

We disabled the hardware prefetcher to make student's lives easier. Consult the ISA manual for your processor generation to determine which MSR should be written to for disabling hardware prefetching.

For our system (`Intel(R) Xeon(R) Gold 5220R CPU @ 2.20GHz`), we used the following configuration:

```
#!/bin/bash

sudo modprobe msr
sudo wrmsr -a 0x1a4 15
```

**Grading**
We suggest a breakdown of the following:

* Part 1- 20% of the total
  * 1 point for correct `1.2.txt`.
  * 1 point for correct `1.4.txt`.
  * 1 point for correct `1.5.txt`.
  * 1 point for correct histogram.
  * Part 1 subscore is out of 4 points.
* Part 2- 50% of the total
  * 5% of part 2 credit is given for a correct answer to DQ6.
  * 95% of part 2 credit is given for a correct chat client. Partial credit can be awarded at the discretion of the TA for partially functional solutions.
* Part 3- 30% of the total
  * 75% of part 3 credit is awarded for a functioning `victim-4` attack.
  * 25% of part 3 credit is awarded for a functioning `victim-3` attack.
  * An additional 25% of credit for part 3 can be awarded for a functioning `victim-2` attack (that is, `victim-2` is extra credit).

```
Part 1 subscore = (1.2 correct + 1.4 correct + 1.5 correct + histogram correct) / 4

Part 2 subscore = (0.05 * DQ6 answer) + (0.95 * chat client score)

Part 3 subscore = (0.75 * victim-4 works) + (0.25 * vicitm-3 works) + (0.25 * victim-2 works)

Total = 0.2 * Part 1 Subscore + 0.5 * Part 2 Subscore + 0.3 * Part 3 Subscore
```

**Advice**
We have found this lab to be the most challenging of the five for a variety of reasons. As this is the student's first microarchitectural attack, there is a steep learning curve to learn how to reason about microarchitectural state. Additionally, the `prime+probe` technique is harder to get right than the `flush+reload` technique we allow in future labs.

While Lab 1 is challenging, we believe it is very rewarding for students to complete, and provides a great foundation for which to build on during in-class discussions and in future labs.

# Lab 2- Spectre
**Learning Objectives**
* Apply an understanding of the cache hierarchy from lab 1 to build a new kind of side channel using shared memory (`flush+reload`).
* Understand how speculative execution works in modern out-of-order machines, and how it leaks information via the microarchitecture.
* Learn about the ISA protections provided by the `x86_64` ring model, and reason about information leakage across privilege boundaries.

**Description**
This lab builds on the foundation we developed in lab 1. Namely, we are going to extend the microarchitectural side channel techniques from lab 1 with the Spectre technique to leak kernel memory from userspace. Students will use the Spectre technique to implement their own `flush+reload` attacks against three vulnerable kernel methods, each one with more protection than the last.

**Setup** We ran this lab on four different physical Intel machines, all of them with the Linux spectre mitigations disabled (`mitigations=off`). This lab can be done using whatever desktop machines your team has lying around (could be the same machine you used for Lab 1).

Student login instructions (as well as which machine they were assigned to) were again emailed to them using a script.

This lab requires the use of a kernel module victim. The kernel module source can be found in `lab2/module-src`. You will need to compile `lab2km.c` and install it as a kernel module on every machine before allowing students to attempt lab 2.

We caution that machines with low memory and no swap space may freeze if students allocate large buffers of memory as part of their attacks. Instructors should beware of this possibility and test their machines extensively before allowing students to attempt the labs.

**Grading**
We suggest a breakdown of the following:

* Part 1 is 35% of the total.
* Part 2 is 40% of the total.
* Part 3 is 25% of the total.

The entire lab is self-grading with `check.py`. The TA can award partial credit at their own discretion for assignments that do not score 100% with the check script. Labs that take too long to run can be stopped following the lab handout timing requirements.

The TA should also allocate points for correct answers to Discussion Questions 1-6. We settled on a 90/10 breakdown (where 90% of each part was awarded for implementation correctness, and 10% was awarded for answers to the Discussion Questions for that part).

# Lab 3- Website Fingerprinting
**Learning Objectives**
* Explore a new kind of side channel from a high level language.
* Understand how to reason about the root cause of misleading microarchitectural observations.
* Develop a real-world website fingerprinting attack that works on modern browsers.

**Description**
In this lab, students implement the techniques from our group's ISCA 2022 paper `There's Always a Bigger Fish: A Case Study of a Misunderstood Timing Side Channel`. Students will begin by implementing a seemingly familiar cache-based side channel attack in Javascript, and will then be asked to reason about why this attack works. Then, students will remove a core part of the attack, but see that the code still works.

**Setup**
Students can complete this lab on their own machines. MacOS, Linux, Windows all should work. Google Chrome is required for Part 4 of this lab.

**Grading**
This lab is graded entirely on the student's solutions PDF. As students may develop their code on a variety of possible systems, the TA should not attempt to grade based on whether the student's code works on the TA machine. Rather, credit should be given for reasonable implementations with a matching solutions document containing well thought-out answers.

* Part 1 is 15% of the total.
* Part 2 is 45% of the total.
* Part 3 is 10% of the total.
* Part 4 is 30% of the total.

# Lab 4- Rowhammer

**Learning Objectives**
* Investigate the physical memory controller and learn how banked DRAM is implemented.
* Implement a double-sided Rowhammer attack to flip bits in a victim address.

**Setup** This lab requires the most effort to set up. Our environment used a job scheduling server (the same machine from lab 2) running HTCondor to schedule jobs across one of three Rowhammer victim machines. These machines were carefully profiled to determine which victim rows are succeptible to Rowhammer. Students were given one of the three machines to use (as usual, emailed to them via a script at the beginning of the lab assignment period). Students were provided with target physical addresses for their machine that course staff had pre-profiled for them (Students were asked to find their own rows as a later part of the assignment). HTCondor was used to handle job scheduling, as each student needs serialized access to the target machine for their attack.

We found that not every machine is easily vulnerable to Rowhammer. We encourage course staff to evaluate their machines extensively before distributing this lab.

**Description**
In a departure from side channel attacks, students will implement a double sided Rowhammer attack to flip victim bits at a specified physical address. Students will learn how to reverse engineer the bank mapping function, and discover their own vulnerable rows.

**Grading**
See the lab handout for our suggested grading scheme for this lab.

# Lab 5- ASLR Bypasses

**Learning Objectives**
* Understand how address-space layout randomization protects software from memory corruption attacks.
* Learn how software prefetchers pose a security risk by revealing which pages are present in the address space.
* Leverage speculative execution once again to probe the address space to learn which pages are present.
* Understand buffer overflows/ code reuse attacks and implement a return-oriented programming attack from assembly instruction gadgets.
* Combine software and hardware attacks to defeat a victim binary using a return oriented programming attack with ASLR defeated via hardware techniques.

**Setup** This lab can reuse the same setup from Lab 2.

**Description**
In this ultimate security lab, students will put all the pieces together from throughout the course to create a full end to end attack against a vulnerable piece of software. Students will learn about modern memory corruption protections, and use hardware side channels to defeat them. Then, students will build a realistic return-oriented programming (ROP) chain using the information leaked through side channels to defeat a victim process.

**Grading**
This lab is entirely self-grading with `check.py`. Instructors can grant partial credit as they see fit for partially functional solutions.

We made the `speculative probing` problem (Part 1C) extra credit.

* Part 1 is 60% of the total.
  * Part 1A is 20% of the total score for lab 5.
  * Part 1B is 40% of the total score for lab 5.
  * Part 1C adds an additional 20% onto the total score for lab 5 if correctly implemented.
* Part 2 is 30% of the total.
  * Part 2A is 10% of the total score for lab 5.
  * Part 2B is 20% of the total score for lab 5.
* Part 3 is 10% of the total.

# Deployment

## Course Machines
As these lab assignments exploit microarchitectural implementation-specific characteristics of modern processors, the deployment process for these labs is bespoke and varied between the labs.

The deployment setup instructions for each lab are described above. Here is a summary of what was discussed in the per-lab sections.

- Lab 1 uses a shared server where each student is allocated one physical core (so, two logical cores that share an SMT core).
- Lab 2 uses any Intel machine with Spectre mitigations off.
- Lab 3 uses student's personal machines.
- Lab 4 uses a carefully inspected Intel machine with a memory controller and DRAM that are known to be vulnerable to Rowhammer.
- Lab 5 reuses the Lab 2 setup.

For every lab, students require bare metal code execution (that is, no virtual machines, containers, etc. should be in between a student's code and the machine).

## Source Distribution
When shipping the course materials, we granted every student their own `git` repo into which they could submit solutions. We automatically pulled student code from their repos at various times to ensure no funny business happened with students modifying commit times after the deadline, etc.

We provided a central course `git` repo that students would fetch from at the beginning of each lab. Here's how we did that:

```
# [TA Machine] In the main course repo:
git checkout --orphan labX
# copy lab code into labX folder. eg:
cp -R /PATH/TO/STARTER/CODE/labX labX
git add labX
git commit -m "Initial Lab X release"
```

```
# [Student's machine] One time setup:
git clone git@github.com:/PATH/TO/STUDENT/LAB.git securehwlabs
cd securehwlabs
git config user.name "MY_STUDENT_ID"
git config user.email "MY_STUDENT_EMAIL"
git remote add lab_release git@github.com:/PATH/TO/COURSE/MAIN/LAB.git
```

```
# [Student's machine] Pulling a new lab to their local repo:
git fetch lab_release
git merge lab_release/labX --allow-unrelated-histories -m "Merging lab code"
git push
```

```
# [Student's machine] Submitting solutions:
git add FILES_YOU_CHANGED
git commit -m "WHAT YOU CHANGED"
git push
```

Students need to run the "One time setup" on each new machine they are asked to work on. This will vary from setup to setup depending on the exact specifications of the course environment. We recommend publishing clear instructions for students on your course website. See our instructions [here](http://csg.csail.mit.edu/6.888Yan/labs/).

It should go without saying that the main repo is read-only to every student, and the student repos are read-write but for just the student and the TA.

### `git` Automatic Deployment (`mk_repo.py`)
`deploy/mk_repo.py` will automatically generate student repositories with the appropriate permissions and add the students to them correctly.

**NOTE** Use the deployment scripts are your own risk. They were built for our environment and may not work for yours.

We maintain a list of students in `students.csv`. This list contains the following keys:
* `name`: The student's human-readable full name.
* `kerb`: The student's kerberos ID. This is synonymous with their GitHub username.

To use `mk_repo.py`:

1. Get your GitHub API token and place it in `token.txt`. (see `mk_repo.py:9`)
1. Create a GitHub organization to put the new repos in.
1. Create the main lab release repository (the one that students can all pull starter code from) in the new organization.
1. Fill in `GITHUB_API`, `ORG_NAME`, and `MAIN_REPO` in `mk_repo.py` accordingly.
1. Fill in `students.csv` with your roster for this semester.
1. Make sure you have the GitHub module (`python3 -m pip install PyGithub`).
1. Run `mk_repo.py`.

You should now see all your student's repositories present in your GitHub organization. Double check the permissions are correct (students have read-write access to their own repo, and everyone has read access to the main lab release repo).
