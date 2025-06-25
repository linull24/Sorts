#!/bin/bash

echo "验证项目文件编码..."
echo "========================"

# 检查源文件编码
echo "源文件编码检查:"
for file in *.c *.h; do
    if [[ -f "$file" ]]; then
        encoding=$(file -bi "$file" | grep -o 'charset=[^;]*' | cut -d= -f2)
        echo "$file: $encoding"
    fi
done

echo ""
echo "文档文件编码检查:"
for file in *.md Makefile; do
    if [[ -f "$file" ]]; then
        encoding=$(file -bi "$file" | grep -o 'charset=[^;]*' | cut -d= -f2)
        echo "$file: $encoding"
    fi
done

echo ""
echo "VSCode配置检查:"
if [[ -d ".vscode" ]]; then
    echo "✓ .vscode目录已创建"
    for config in settings.json tasks.json launch.json; do
        if [[ -f ".vscode/$config" ]]; then
            echo "✓ $config 已创建"
        else
            echo "✗ $config 缺失"
        fi
    done
else
    echo "✗ .vscode目录不存在"
fi

echo ""
echo "编码验证完成！"