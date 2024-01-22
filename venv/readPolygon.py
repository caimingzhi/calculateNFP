import re

# 定义一个包含电子邮件地址的文本
text = "我的电子邮件地址是: user@example.com，另一个地址是：another.email123@domain.co"

# 使用正则表达式匹配电子邮件地址
email_pattern = r'\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,7}\b'
matches = re.findall(email_pattern, text)

# 打印匹配的电子邮件地址
for match in matches:
    print(match)
