echo "Please enter today's date in this form : /dd/mm/yyyy : "
read date

echo "git add ."
git add .

echo "git commit -m (date)"
git commit -m "${date}"

echo "git satus"
git status

echo "pull"
git pull

echo "push"
git push git@github.com:orbiay/Webserv_v2.git master

echo "done"
