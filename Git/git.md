$git add filename
$将修改添加到暂存区
$git rm filename
$删除文件
$git commit -m "about"
$提交暂存区的所用修改
$git status
$查看状态


$git remote add origin git@github.com:username/reposityname.git
$在本地目录下关联远程仓库
$git remote remove origin
$取消本地目录下关联的远程仓库


$git push -u origin master$
第一次把本地库的所有内容推送到远程库,之后可以去掉-u





git连接github
第一步：
$ssh-keygen -t rsa -C "youremail@example.com"
$你需要把邮件地址换成你自己的邮件地址，然后一路回车，使用默认值即可，由于这个Key也不是用于军事目的，所以也无需设置密码。

如果一切顺利的话，可以在用户主目录里找到.ssh目录，里面有id_rsa和id_rsa.pub两个文件，这两个就是SSH Key的秘钥对，id_rsa是私钥，不能泄露出去，id_rsa.pub是公钥，可以放心地告诉任何人。

第二步：
登陆GitHub，打开“Account settings”，“SSH Keys”页面
点“Add SSH Key”，填上任意Title，在Key文本框里粘贴id_rsa.pub文件的内容
点“Add Key”，你就应该看到已经添加的Key

GitHub允许你添加多个Key
