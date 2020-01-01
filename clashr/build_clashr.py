import subprocess
import datetime
import plistlib
import platform
import os

def get_version():
    with open('./go.mod') as file:
        for line in file.readlines():
            if "clash" in line and "shadowclash" not in line:
                return line.split(" ")[-1].strip()
    return "unknown"


def build_clash(version):
    build_time = datetime.datetime.now().strftime("%Y-%m-%d-%H%M")
    if platform.system() == "Linux":
        command = """go build -ldflags '-X "github.com/TheWanderingCoel/clash/constant.Version={version}" \
        -X "github.com/TheWanderingCoel/clash/constant.BuildTime={build_time}"' \
        -buildmode=c-archive """
    else:
        command = """go build -buildmode=c-archive """
    subprocess.check_output(command, shell=True)
    try:
        os.system("mv shadowclash.h ../src")
        os.system("mv shadowclash.a ../framework")
    except Exception as e:
        print(e)

def write_to_info(version):
    path = "info.plist"

    with open(path, 'rb') as f:
        contents = plistlib.load(f)

    if not contents:
        exit(-1)

    contents["coreVersion"] = version
    with open(path, 'wb') as f:
        plistlib.dump(contents, f, sort_keys=False)


def run():
    version = get_version()
    print("current clashr version:", version)
    build_clash(version)
    print("build static library complete!")
    """
    if os.environ.get("CI", False):
        print("writing info.plist")
        write_to_info(version)
    """
    print("done")


if __name__ == "__main__":
    run()
