# 我生平第一个工程——AI五子棋😋
## 概要

----------------------------------------------
本项目是我大一的第一个项目，学会了棋类博弈的许多知识，比如极小化极大值搜索和其简化后的负极大值算法以及剪枝算法，
同时对哈希函数由于c++基础较差，Zobrist函数有了一定了解。
由于c++不够熟悉，仅使用了STL和一部分类的用法，在结构方面可能存在一定问题

## 我学到了什么

----------------------------------------------
1. 首先是为什么自顶向下的方法和思维。这种思维有利于一个工程的构建。它能使得问题分解成更小的子问题，这些子问题可以更容易地解决。使得问题就不再是一个复杂无法处理的单个整体，而是一系列可以更容易处理的子问题。
2. 还有模块化的思想和方法。它可以被多次使用，便于维护，易于理解测试和拓展。其提高了代码的效率和质量。
3. 对于debug和测试更加熟练。编写一个这样的程序，大部分时间花在了debug上，这让我对断点以及其他调试方法有了更熟练的应用。
4. 提高了对c++的认识。虽然是c语言课程的实验，但是c++的一些特性比如面向对象编程更好的给出了代码的结构，另一些比如STL，大大方便了代码的编写，同时降低了程序员的工作量。
5. 了解了棋类以及博弈有关的一些算法，对于以后的学习有了一定的准备。

## 关于此五子棋AI

----------------------------------------------
此AI达成`6`层深度的dfs加上`8`层“算杀”。此棋力较强但仍然不能与专业选手一较高下。因此，暂时不考虑禁手，以给与AI获胜的机会。

### 结构、思路与实现

----------------------------------------------
- 使用easyX库作为图形界面
- 在 *board.h/board.cpp* 中封装了落子、悔棋、评分等与棋局有关的函数。
- 在 *point.h/point.cpp* 中封装了点位信息以及得分，可以从board类中快速读取对应点位与得分用于评估局势。
- 在 *role.h/role.cpp* 中封装了角色对应棋子颜色和反转颜色函数，用于negamax搜索。
- 在 *AI.h/AI.cpp* 中封装了negamax、剪枝、迭代、算杀、AI下棋等与AI有关的函数
- 在 *GUI.h/GUI.cpp* 中封装了图形界面初始化、字体设置、人类走棋等函数
- 同时使用.rc文件将背景图编译进程序中便于程序传播测试。

#### 项目思路
1. 计算出图片格子坐标，使用鼠标点击模拟下棋。关于坐标信息存放在 *GUI.h* 中。如果鼠标点击时坐标在某个范围中即视为有效点击，在棋盘上绘图出棋子，并在二维数组中更新。
2. 计算机通过计算获取最佳点位（储存在std::pair中），并在棋盘和数组中更新。
3. 如果电脑先走，则在`（7，7）`或者`（8，8）`中随机选择一个下棋。

#### 具体实现
- 对于人类下棋在 *GUI.cpp*中


    void GUI::HumanDo() {
        while(true) {
            //检测鼠标点击
            mouse.lbutton = false;
            while (!mouse.lbutton) {
                getmessage(&mouse, EX_MOUSE);
            }
            mouse.lbutton = false;
            //遍历棋盘
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    //查看鼠标是否在正确位置
                    if (mouse.x > X[i] - 16 && 
                        mouse.x < X[i] + 16) {
                        if (mouse.y > Y[j] - 16 && mouse.y < Y[j] + 16 
                            && board.board[i][j] == 0) {
                            
                            ......
                        
                        }
                    }
                }
            }
        }
    }

- 电脑下棋：主要通过negamax获取最佳点位。
````
int AI::negamax(int deep, int alpha, int beta, int role, std::vector<point> &candidates) {
    int v;
    int best = MIN;

    for (auto & candidate : candidates) {
        pair<int,int>p = candidate.coor;
        board.put(p, role);
        v = -r(deep - 1, -beta, -alpha, R.trans(role));
        board.remove(p,role);
        alpha = max(best, alpha);
        
        //标记每个候选点的分数，之后再用sort排序，随机选取最大得分的点
        
        candidate.score = v;
        if(v > best){
            best = v;
        }
    }
    return alpha;
}
````
其中的int r(int,int,int,int,vector<point>)函数是集成了算杀模块的negamax，原理相同。
````
int AI::r(int deep, int alpha, int beta, int role) {
    int v = board.score(role);
    if(deep <= 0 || GUI::WinCondition()){
        return v;
    }

    int best = MIN;

    vector<point>candidates;
    board.GenerateBoard(deep, role, candidates);

    for (auto & candidate : candidates) {
        pair<int,int>p = candidate.coor;
        board.put(p, role);
        alpha = max(best, alpha);
        //迭代
        v = -r(deep - 1, -beta, -alpha, R.trans(role));
        board.remove(p,role);
        if(v > best){
            best = v;
        }
        //剪枝
        if(v >= beta){
            return v;
        }
        //迭代加深+算杀
        if(deep <= 2 && role == R.com && 
        best < FOUR_SCORE && best > (FOUR_SCORE * (-1))){
            vector<point>mate;
            bool m = kill(role, 8, mate);
            if(m){
                return FIVE_SCORE * pow(0.8,(double)mate.size());
            }
        }
    }
    return best;
}
````
- 算杀模块也是运用minimax来获取最佳点位，但只计算活三活四，因此可以达到`8`层的深度。具体代码与negamax相似，不再列出。
- 局势评估函数：封装再board类中的score中，通过计算每一个点的得分来计算总分，每下一步更新一次，具体代码详见ScorePoint函数
````
//方向向上，其他方向与之类似
    for (int i = y; TRUE; ++i) {
        if (i >= 15) {
            block++;
            break;
        }
        int t = board[x][i];
        if (t == R.emp) {
            if (empty == -1 && i < 14 && 
            board[x][i + 1] == role) {
                empty = count;
                continue;
            } else {
                break;
            }
        } else if (t == role) {
            count++;
            continue;
        } else if (i == y && t != role && t != R.emp) {
            block++;
        } else {
            block++;
            break;
        }
    }
````

- 启发式搜索函数：封装在board类中，依赖于ScorePoint函数，之后按照成五、活四、活三、死四等排列输出，对于减少negamax计算量有显著效果，具体代码过长，见 *board.cpp* .

### 运行效果
效果较好，但偶尔有盲目冲四的问题。可以战胜五子棋新手但在老手方面仍有不足。由于没有学习，之前下错的步骤之后仍然不会改正，影响实际效果。希望在之后学习更多知识后能改进这个问题。
![](https://i.niupic.com/images/2023/02/18/akvj.jpg)

![](https://i.niupic.com/images/2023/02/18/akvh.jpg)

![](https://i.niupic.com/images/2023/02/18/akvi.jpg)

## 参考

----------------------------------------------
主要参考了以下大神的文章以及维基百科：
>1. https://github.com/lihongxun945/myblog
>2. https://www.bilibili.com/BV1bT4y1C7P5
>3. https://en.wikipedia.org/wiki/Zobrist_hashing