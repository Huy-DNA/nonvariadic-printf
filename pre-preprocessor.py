import sys
import re

printfPattern = re.compile(r"my_printf\s*\(([^,;()]*)((?:,[^,;()]*)*)\)\s*;", re.MULTILINE | re.DOTALL)
def printfSubstitute(match):
    def getWriteParamString(param):
        return f"""
            p_last = (char*)p_last - 1; // avoid the std::align pitfall
            __realign(p_last, decltype({param} + 0));
            *(decltype({param} + 0)*)p_last = {param};
            p_last = (decltype({param} + 0)*)p_last + 1;
        """

    statement = match.group(0)
    print("Detected: " + statement)

    formatString = match.group(1)
    params = match.group(2).split(',')[1:]

    paramWriteStatements = ''.join([getWriteParamString(param) for param in params])

    return f"""{{
        void* __internal_buffer = malloc(10000);
        void* p_last = __internal_buffer;

        {paramWriteStatements}

        _my_printf_({formatString}, __internal_buffer);

        free(__internal_buffer);
    }}
    """

if __name__ == '__main__':
    if len(sys.argv) < 2:
        exit("Error: At least one source file should be applied.")

    sourceNameList = sys.argv[1:]
    for sourceName in sourceNameList:
        sourceContent = ""
        with open(sourceName, 'r') as sourceFile:
            sourceContent = sourceFile.read()
            sourceContent = printfPattern.sub(printfSubstitute, sourceContent)
        
        with open(f"{sourceName[:-4]}.output.cpp", 'w') as sourceFile:
            sourceFile.write(sourceContent)