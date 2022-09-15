import sys
import argparse

RED     = "\033[1;31m"
NATURAL = "\033[0m"

parser = argparse.ArgumentParser(description="Script create commands for converting source file to object files")

parser.add_argument("--cc",      type=str)
parser.add_argument("--src_ext", type=str)
parser.add_argument("--obj_ext", type=str)
parser.add_argument("files",     type=str, nargs="*", default="None")


def get_commands(cmd_args):
    if len(sys.argv) < 2:
        return -1, "Incorret arguments amount"
    
    src_files = list(filter(lambda file: file.endswith(cmd_args.src_ext), cmd_args.files))
    obj_files = list(filter(lambda file: file.endswith(cmd_args.obj_ext), cmd_args.files))

    if len(src_files) != len(obj_files):
        return -2, f"len(src_files) != len(obj_files) | src_files={src_files} | obj_files={obj_files}"
    
    if len(src_files) == 0 or len(obj_files) == 0:
        return -3, f"No files with '{cmd_args.src_ext if len(src_files) == 0 else cmd_args.obj_ext}' extension."

    return 0, [f"{cmd_args.cc} -c {src_files[i]} -o {obj_files[i]}" for i in range(len(src_files))]


if __name__ == "__main__":
    args = parser.parse_args()

    exit_code, result = get_commands(args)

    if exit_code == 0:
        sys.stdout.write(" | ".join(result) + "\n")
    else:
        sys.stdout.write(RED + f"Error occured in python script: '{result}'. exit code {exit_code}" + NATURAL)
