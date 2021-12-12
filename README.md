## LR(0)分析法研究

1. 文法使用产生式来定义；
2. 给出项目集规范族（即所有的状态）。
3. 给出状态间的关系。
4. 给出LR(0)分析表。
5. 给定符号串判定它是否是文法中的句子，分析过程用分析表格的方式打印出来。

### 目前已经解决的问题：

没有有环的图没有问题

**example**

<img src="./.github/exp.png" style="zoom: 33%;" />

```bash
Please Enter a LR(0) grammar.
A line stands for one statement
type "->" refers to transfer to an sentences
First, please enter the numbers of the sentences:
4
Enter the LR(0) Grammar:
[1] > S->aAcBe
[2] > A->b
[3] > A->Ab
[4] > B->d
I0:
' -> @S
S -> @aAcBe
I1: S
' -> S@
I2: a
S -> a@AcBe
A -> @b
A -> @Ab
I3: A
S -> aA@cBe
A -> A@b
I5: c
S -> aAc@Be
B -> @d
I7: B
S -> aAcB@e
I9: e
S -> aAcBe@
I8: d
B -> d@
I6: b
A -> Ab@
I4: b
A -> b@
```

---------------------------------------

**NOTE** 
12.31日之前完成任务

### 问题：

<img src="./.github/exp01.png" style="zoom: 50%;" />

1. 一个自己循环的节点目前没有什么好方法识别
2. 两个项目集规范族指向同一个项目集规范族没有解决