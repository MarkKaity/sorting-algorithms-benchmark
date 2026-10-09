#!/bin/bash

echo "=== GITHUB UPLOAD SCRIPT ==="

# 1. Tao file .gitignore neu chua co
if [ ! -f .gitignore ]; then
    echo "Tao file .gitignore de loai bo cac file .exe..."
    echo "*.exe" > .gitignore
    echo "*.pdb" >> .gitignore
fi

# 2. Khoi tao Git
if [ ! -d .git ]; then
    echo "Khoi tao Git repository..."
    git init
fi

# 3. Add va Commit
echo "Dang them file vao Git..."
git add .
git commit -m "Hoan thanh source code va bao cao thu nghiem sorting"

# 4. Yeu cau nhap URL repo
echo ""
echo "Vui long tao mot Repository TRONG tren GitHub (khong co README)."
read -p "Dien duong dan GitHub Repository cua ban (vd: https://github.com/user/repo.git): " REPO_URL

if [ -n "$REPO_URL" ]; then
    git branch -M main
    
    # Kiem tra xem da co remote origin chua
    if git remote | grep -q "^origin$"; then
        git remote set-url origin "$REPO_URL"
    else
        git remote add origin "$REPO_URL"
    fi

    echo "Dang day (push) ma nguon len GitHub..."
    git push -u origin main
    echo "Hoan thanh!"
else
    echo "Ban da bo qua viec nhap URL. Xin vui long chay thu cong lenh 'git remote add origin ...' va 'git push'."
fi

