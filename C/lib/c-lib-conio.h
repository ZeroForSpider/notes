
-------------------------
conio					 |
-------------------------
int _getch();
	* 该函数从标准的io流中返回一个 char
	* 当用户输入一个字符,就会立即返回,不会根据空格/换行等切割
	* demo
		char ch = _getch();
		printf("%c",ch);
