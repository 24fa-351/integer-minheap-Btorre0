echo "Running tests..."
echo

if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
    exit 1
fi

echo "Running the program..."
./main > output.txt

if [ $? -eq 0 ]; then
    echo "Program ran successfully :)"
    echo "Output captured in output.txt"
else
    echo "Program failed :("
    exit 1
fi

echo "Displaying the contents of output.txt:"
cat output.txt
