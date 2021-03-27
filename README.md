# Compilation-principle-experiment-of-hbut
> 湖北工业大学————编译原理实验

## 实验一
词法分析程序设计

## 实验二
递归向下语法分析程序设计
>【编译原理实验二思考题】

### （1） 你所编制的程序与实验1 程序有何联系，如何应用实验1。

在实验一中，主要功能函数scanner（）可以扫描用户输入的字符串，并将其根据关键字、运算符、界符、标识符（ID）和整形常数（NUM)分类识别

在实验二中，语法分析程序中的语句串分析函数yucu（）、语句分析函数statement（）、表达式分析函数expression（）、注释处理函数term（）和因子分析函数factor（）中都需要调用scanner（）以识别各类词素模式，从而识别相应语法正误



### （2） 将源程序放置在文本文件中，运用流操作实现对源程序的扫描和分解，编程实现。

实现部分代码

```c++
//运用流操作读取存放源程序的文本文件ceshi.txt
	char str;
	p = 0;
	ifstream inFile("ceshi.txt", ios::in | ios::binary); //二进制读方式打开所需读取的源程序
	if (!inFile) {
		cout << "error" << endl;
		return 0;
	}
	while (inFile.read((char*)&str, sizeof(str))) { //一直读到文件结束
		prog[p++] = str;
	}
	p = 0;
	ch = prog[p];
	while (prog[p] != NULL) {
		cout << prog[p++];
	}
	cout << endl;
	//将prog指针赋初值，对源程序进行词法、语法分析
	p = 0;
	ch = prog[p];
	scanner();
	Irparser();
```

运行结果

![image-20210327093947421](https://yzw-0608-1301840939.cos.ap-chengdu.myqcloud.com/undefined/202103/27/093951-449581.png)

![image-20210327094042447](https://yzw-0608-1301840939.cos.ap-chengdu.myqcloud.com/undefined/202103/27/094044-201553.png)

## 实验三
SLR(1)，LR(1)等分析方法的程序实现

## 实验四
自动机应用，利用自动机技术和原理解决实际问题
