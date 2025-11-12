import os, json, datetime, re

root = os.getcwd()
out_dir = os.path.join("work", "typst")
out_file = os.path.join(out_dir, "all.typ")
os.makedirs(out_dir, exist_ok=True)

levels = ["=", "==", "===", "====", "=====", "======"]

def convert_math(text: str) -> str:
 if not text:
  return text;

 def disp_display(m):
  content = m.group(1).strip()
  content = content.replace("`", "\\`")
  return "\n#mitex(`\n" + content + "\n`)\n"

 def disp_inline(m):
  content = m.group(1).strip()
  return f"#mi({json.dumps(content)})"
 
 text = re.sub(r"\$\$(.*?)\$\$", disp_display, text, flags=re.S)
 text = re.sub(r"\\\[(.*?)\\\]", disp_display, text, flags=re.S)
 text = re.sub(r"(?<!\$)\$(?!\$)(.*?)(?<!\$)\$(?!\$)", disp_inline, text)
 text = re.sub(r"\\\((.*?)\\\)", disp_inline, text)
 return text

def write_text(f, s):
 if s is None:
  return;
 f.write(s.replace("\r\n","\n").replace("\r","\n"))

today = datetime.date.today().isoformat()
header = [
 r'#import "@preview/mitex:0.2.5": *',
 r'#import "@preview/cuti:0.3.0": show-cn-fakebold',
 r"#show: show-cn-fakebold",
 r'#set page(numbering: "1")',
 r"#set text(font: (",
 r'(name: "SimSun", covers: regex("[\u{4E00}-\u{9FFF}]")),',
 r'(name: "Times New Roman", covers: "latin-in-cjk"),',
 r"))",
 r"#align(horizon)[",
 r'  #text(size: 30pt, "Algorithm\n")',
 r"",
 r"  #text(size: 14pt)[",
 r"    作者: lhc0707",
 r"",
 f"    最后一次修改：{today}",
 r"  ]",
 r"]",
 r"#pagebreak()",
 r"#outline()",
 r"#pagebreak()",
]

with open(out_file, "w", encoding="utf-8", newline="\n") as typ:
 for i in header:
  write_text(typ, i + "\n")
 
 def gci(filepath, rootpath):
  try:
   files = os.listdir(filepath)
  except Exception:
   return
  if ".makelatex-ignore" in files or ".git" in filepath or ".vscode" in filepath:
   return
  
  root_parts = os.path.normpath(rootpath).split(os.sep)
  cur_parts = os.path.normpath(filepath).split(os.sep)
  depth_diff = len(cur_parts) - len(root_parts)

  folder_name = os.path.basename(filepath)
  folder_name = convert_math(folder_name)

  if depth_diff > 0:
   lvl = min(depth_diff - 1, len(levels) - 1)
   write_text(typ, f"{levels[lvl]} {folder_name}\n\n")
  
  for fi in sorted(files):
   fi_d = os.path.join(filepath, fi)
   if not os.path.isdir(fi_d) and fi_d.endswith(".cpp"):
    try:
     with open(fi_d, encoding="utf-8", newline="") as f:
      code = f.read()
    except Exception:
     continue

    title = fi.replace("_", " ")
    brief = ""
    if code.startswith("//"):
     first = code.split("\n", 1)[0]
     rest = code.split("\n", 1)[1] if "\n" in code else ""
     try:
      meta = first.split("//", 1)[1]
      dc = json.loads(meta)
      title = dc.get("name", title)
      brief = dc.get("intro", title)
      code = rest
     except Exception:
      code = code
     
     title = convert_math(title)
     brief = convert_math(brief)

     lvl = min(depth_diff, len(levels) - 1)
     write_text(typ, f"{levels[lvl]} {title}\n\n")
     if brief:
      write_text(typ, brief + "\n\n")

     write_text(typ, "```cpp\n")
     write_text(typ, code.rstrip("\n") + "\n")
     write_text(typ, "```\n")
 
 gci(root, root)