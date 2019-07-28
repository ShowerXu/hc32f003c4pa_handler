echo "# hc32f003c4pa_handler" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/htxiaofeng/hc32f003c4pa_handler.git
git push -u origin master

…or push an existing repository from the command line
git remote add origin https://github.com/htxiaofeng/hc32f003c4pa_handler.git
git push -u origin master


使用方法：
1.添加改变文件：git add .
2.添加修改说明  git commit -m "修改README说明"
3.上传服务器    git push -u origin master

 同步服务器软件：git pull


20190728://steve
1.UART1可以发送接收数据。
2.增加P23输出38K脉冲。
3.修改AD功能。
