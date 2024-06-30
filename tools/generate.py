import os
import argparse
import sys

def read_template(template_file):
    with open(template_file, 'r') as file:
        return file.read()

def create_project(class_name):
    # Capitalize the first letter of the class name for the source stubs
    class_name_cap = class_name.capitalize()

    # Define the path to the templates directory
    templates_dir = os.path.join(os.path.dirname(__file__), 'templates')

    # Read the template contents
    cmakelists_template = read_template(os.path.join(templates_dir, 'CMakeLists.txt.template'))
    test_cpp_template = read_template(os.path.join(templates_dir, 'test.cpp.template'))
    test_main_cpp_template = read_template(os.path.join(templates_dir, 'test_main.cpp.template'))
    header_template = read_template(os.path.join(templates_dir, 'header.hpp.template'))
    source_template = read_template(os.path.join(templates_dir, 'source.cpp.template'))

    # Create the target directories
    test_dir = os.path.join(os.path.dirname(__file__), '..', 'test', class_name)
    src_dir = os.path.join(os.path.dirname(__file__), '..', 'src', class_name)

    for directory in [test_dir, src_dir]:
        if not os.path.exists(directory):
            os.makedirs(directory)

    # Define the files to be created
    test_files = {
        'CMakeLists.txt': cmakelists_template,
        f'test_{class_name}.cpp': test_cpp_template,
        f'test_{class_name}_main.cpp': test_main_cpp_template
    }
    src_files = {
        f'{class_name}.hpp': header_template,
        f'{class_name}.cpp': source_template
    }

    # Check if any file already exists
    for directory, files in [(test_dir, test_files), (src_dir, src_files)]:
        for filename in files:
            if os.path.exists(os.path.join(directory, filename)):
                print(f"Error: The file '{filename}' already exists in '{directory}'.")
                sys.exit(1)

    # Replace placeholders and create the test files
    for filename, content in test_files.items():
        with open(os.path.join(test_dir, filename), 'w') as file:
            file.write(content.replace('{{CLASS_NAME}}', class_name).replace('{{CLASS_NAME_CAP}}', class_name_cap))
    
    # Replace placeholders and create the source files
    for filename, content in src_files.items():
        with open(os.path.join(src_dir, filename), 'w') as file:
            file.write(content.replace('{{CLASS_NAME}}', class_name).replace('{{CLASS_NAME_CAP}}', class_name_cap))
    
    # Update the test CMakeLists.txt file
    test_cmake_file = os.path.join(os.path.dirname(__file__), '..', 'test', 'CMakeLists.txt')
    subdirectory_entry = f'add_subdirectory({class_name})\n'

    if os.path.exists(test_cmake_file):
        with open(test_cmake_file, 'r') as file:
            lines = file.readlines()
        
        if subdirectory_entry not in lines:
            with open(test_cmake_file, 'a') as file:
                file.write(subdirectory_entry)
    
    # Update the src CMakeLists.txt file
    src_cmake_file = os.path.join(os.path.dirname(__file__), '..', 'src', 'CMakeLists.txt')
    if os.path.exists(src_cmake_file):
        with open(src_cmake_file, 'r') as file:
            lines = file.readlines()

        # Add the new source directory to the SOURCES variable within the parentheses
        sources_entry = f'		${{PROJECT_SOURCE_DIR}}/src/{class_name}/*.cpp\n'
        sources_index = next((i for i, line in enumerate(lines) if line.strip().startswith('file(GLOB_RECURSE SOURCES')), -1)
        if sources_index != -1:
            while not lines[sources_index].strip().endswith(')'):
                sources_index += 1
            lines.insert(sources_index, sources_entry)
        
        # Add the new include directory to the target_include_directories within the parentheses
        include_entry = f'		{class_name}\n'
        include_index = next((i for i, line in enumerate(lines) if line.strip().startswith('target_include_directories(${NAME} PRIVATE')), -1)
        if include_index != -1:
            while not lines[include_index].strip().endswith(')'):
                include_index += 1
            lines.insert(include_index, include_entry)
        
        with open(src_cmake_file, 'w') as file:
            file.writelines(lines)

    print(f"New Class '{class_name}' has been created successfully with stubs in 'test' and 'src' folders!")

def main():
    parser = argparse.ArgumentParser(description="Generate a C++ test project from a template.")
    parser.add_argument("class_name", help="Name of the class to be created.")
    args = parser.parse_args()
    
    create_project(args.class_name)

if __name__ == "__main__":
    main()
