import subprocess
LOG_FILE = "modistarc_results"

def quit_kermit():
    subprocess.run(["bash", "-c", "kill -9 `pgrep wermit`"])

# This function was grabed from Stackoverflow
# @Source: https://stackoverflow.com/questions/4417546/constantly-print-subprocess-output-while-process-is-running
def execute(cmd):
    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, universal_newlines=True)
    for stdout_line in iter(popen.stdout.readline, ""):
        if stdout_line.startswith("## Ready for binary (kermit) download to 0xC1000000 at 115200 bps..."):
            quit_kermit()
        yield stdout_line 

    popen.stdout.close()

f = open(LOG_FILE, "a")

# Example
for line in execute(["third_party/wermit/wermit", "kermit_upload"]):
    line = line.lstrip()
    if line.startswith("ECC") or line.startswith("BCC"):
        print(line, end="\r")
        f.write(line)
    