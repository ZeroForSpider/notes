----------------------------
文件编程					|
----------------------------
	# 文件的类型
		* 设备文件,设备也可以当做文件,具备io
		* 磁盘文件

	# 打开文件
		FILE *fopen( const char * filename, const char * mode );
		
		* 打开一个文件,name指定文件地址,model指定打开的类型
		* model的枚举字符串
			r	打开一个已有的文本文件,允许读取文件

			w	打开一个文本文件,允许写入文件,如果文件不存在,则会创建一个新文件
				在这里,程序会从文件的开头写入内容,如果文件存在,则该会被截断为零长度,重新写入

			a	打开一个文本文件,以追加模式写入文件,如果文件不存在,则会创建一个新文件
				在这里,程序会在已有的文件内容中追加内容

			r+	打开一个文本文件,允许读写文件

			w+	打开一个文本文件,允许读写文件,如果文件已存在,则文件会被截断为零长度
				如果文件不存在，则会创建一个新文件

			a+	打开一个文本文件,允许读写文件,如果文件不存在,则会创建一个新文件,读取会从文件的开头开始,写入则只能是追加模式
		
		*  处理的是二进制文件,则需使用下面的访问模式来取代上面的访问模式：
			"rb", "wb", "ab", "rb+", "r+b", "wb+", "w+b", "ab+", "a+b"
		
		* 如果打开失败,返回 NULL
			FILE *file = fopen("d.txt","r");
			if (file == NULL){
				perror("fopen");	//fopen: No such file or directory
				return EXIT_FAILURE;
			}
		* 注意,该结构体是在堆空间分配的,使用完成后要释放
		* 文件的打开,可以是相对路径,也可以是绝对路径
			fopen("./d.txt","r");


	# 关闭文件
		int  fclose (FILE *);
	
	# 刷出缓冲区
		int fflush (FILE *);
	
	# 重定向文件
		FILE * freopen (const char *, const char *, FILE *);
	
	# FILE 结构体的属性
		typedef struct _iobuf
		{
		  char	*_ptr;
		  int	 _cnt;
		  char	*_base;
		  int	 _flag;
		  int	 _file;
		  int	 _charbuf;
		  int	 _bufsiz;
		  char	*_tmpfname;
		} FILE;

		typedef struct 
		{
			short			level;		//缓冲区状态,满或者空
			unsigned		flags;		//文件状态标识
			char			fd;			//文件描述符
			unsigned char	hold;		//如无缓冲区不读取字符
			short			bsize;		//缓冲区大小
			unsigned char	*buffer;	//缓冲区数据位置
			unsigned		ar;			//指针,当前的指向
			unsigned		istemp;		//临时文件,指示器
			short			token;		//用于有效性的检查
		} FILE;
	

----------------------------
文本文件的读写				|
----------------------------
	# 读取/写入单个字符
		fgetc( FILE * fp );
			* fgetc() 函数从 fp 所指向的输入文件中读取一个字符,返回值是读取的字符
			* 如果发生错误则返回 EOF,(-1)
		
		fputc( int c, FILE *stream );
			* 用于把单个字符写入stream指定的文件中
			* 果写入成功,它会返回写入的字符,如果发生错误,或者读取到了末尾,则会返回 EOF(-1)
		
	# 读取/写入字符串
		fgets(char *s,int size,FILE stream)
			* 参数
				s: 字符串
				size:指定读取最大字符串的长度(默认 -1,不限制)
				stram:文件指针,'如果读取键盘输入的字符串,固定为stdin'
			* 从stream指定的文件内读入字符,保存到s指定的内存空间,直到出现换行字符,读取到文件结尾,或是已经读取了size - 1 个字符为止
			* 会自动在最后加上 '\0' 标识,会把换行符也一起读取进去
			* s最多只能装 length - 1个字符,因为必须要留一个给字符串结束符 '\0',如果输入内容大于了 size 或者 sizeof(s) 那么超出部分会被截断
			* 读取成功返回读取到的字符串,读取到文件末尾或者出错,返回 NULL
			* 读取文件
				FILE *file = fopen("E:\\c-lang.txt","r");
				char buf[1024];
				char *r = fgets(buf,sizeof(buf) - 1,file);
				while(r != NULL){
					printf("%s",buf);
					r = fgets(buf,sizeof(buf) - 1,file);
				}
		
		fputs(const char *str,FILE *stream)
			* 把 str 字符写入到stream指定的文件中,字符串结束符 '\0' 不写入文件
			* 成功返回 0,失败返回 EOF(-1)
			* 可以把stream替换为 stdout,使str被输出到屏幕
		
	

	# 格式化流输出		fprintf(FILE *fp,const char *format, ...)
		* 源是变量,目标是文件

		FILE *file = fopen("E:\\c-lang.txt","w+");
		fprintf(file,"Hello KevinBlany ,Im %s","Java");
		fclose(file);
		
	
	# 格式化流输入		int fscanf(FILE *fp, const char *format, ...) 
		* 源是文件,目标是变量
		* 函数来从文件中读取字符串,但是在遇到第一个空格字符时,它会停止读取

		FILE *file = fopen("E:\\c-lang.txt","r");
		int x,y,z;
		fscanf(file,"%d %d %d",&z,&y,&z);
		printf("z=%d,y=%d,z=%d",z,y,z);		//z=36,y=12,z=36
		fclose(file);
	
	# 判断文件是否读取到了末尾
		* 文本文件的末尾会有一个隐藏的-1(EOF),表示文件已经结束
		* 二进制文件末尾没有-1标识,因为-1可能是文件中的数据,同过 -1 来判断不靠谱
		* 可以通过 feof() 来判断文件是否读取到了末尾,不论是二进制文件还是文本文件
		* feof(); 返回 bool
			FILE *file = fopen("c.txt","r");

			bool end = feof(file);
			printf("%d",end);		//0

		* 它其实是判断你读取后的数据,是不是末尾标识,也就是说要先读取了末尾标识,所以,一般先读取,再判断
			fgetc(file);
			if(feof(file)){
				break;
			}
			....
	

----------------------------
随机io						|
----------------------------
	int fseek (FILE *file, long offset, int whence); 
		* fseek 设置当前读写点到 offset 处
		* whence 可以是 SEEK_SET,SEEK_CUR,SEEK_END 这些值决定是从文件头,当前点,文件尾	计算偏移量 offset
		* 相对当前位置往后移动一个字节:fseek(fp,1,SEEK_CUR);
		* 往前移动一个字节.直接改为负值就可以:fseek(fp,-1,SEEK_CUR)

			FILE *file = fopen("E:\\c-lang.txt","r+");
			//指针移动到第10个字节
			fseek(file,10,SEEK_SET);
			//把第10个字节替换为'A'
			if(fputc('A',file) == EOF){
				printf("异常");
			}
			fclose(file);

		* 只有用 r+ 模式打开文件才能插入内容,w 或 w+ 模式都会清空掉原来文件的内容再来写
		* a 或 a+ 模式即总会在文件最尾添加内容,哪怕用 fseek() 移动了文件指针位置

----------------------------
二进制文件的读写			|
----------------------------
	
	size_t fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
				  
	size_t fwrite(const void *ptr, size_t size_of_elements,size_t number_of_elements, FILE *a_file);

	# 这两个函数都是用于存储块的读写 - 通常是数组或结构体