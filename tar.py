import os
import tarfile
import argparse

def find_and_combine_files(input_folder, output_folder):
    for dirpath, _, filenames in os.walk(input_folder):
        rel_path = os.path.relpath(dirpath, input_folder)
        output_dir = os.path.join(output_folder, rel_path)
        os.makedirs(output_dir, exist_ok=True)

        base_names = set(f.split('.')[0] for f in filenames)

        for base in base_names:
            matching_files = [f for f in filenames if f.startswith(base + ".")]
            if len(matching_files) > 1:
                tar_path = os.path.join(output_dir, f"{base}.tar")
                with tarfile.open(tar_path, "w") as tar:
                    for file in matching_files:
                        tar.add(os.path.join(dirpath, file), arcname=file)
                print(f"Created: {tar_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Combine matching files into tar archives while maintaining folder structure.")
    parser.add_argument("input_folder", help="Path to the input folder")
    parser.add_argument("output_folder", help="Path to the output folder")
    args = parser.parse_args()

    if os.path.isdir(args.input_folder):
        os.makedirs(args.output_folder, exist_ok=True)
        find_and_combine_files(args.input_folder, args.output_folder)
    else:
        print("Invalid input folder path.")
