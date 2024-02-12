int main(int argc, char** argv)
{
	char* fileName;

	if (argc >= 2) {
		fileName = argv[1];
	}

	std::cout << fileName;

	return 0;
}
