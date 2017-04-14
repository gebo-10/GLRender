char * ShaderProgram::readTextFile(char * file_name) {
	char *buffer = 0;
	std::ifstream t;
	int length;
	t.open(file_name, ios::binary);      // open input file  
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  
	buffer = new char[length + 1];    // allocate memory for a buffer of appropriate dimension  
	t.read(buffer, length);       // read the whole file into the buffer  
	buffer[length] = '\0';
	t.close();                    // close file handle  
	return buffer;
}