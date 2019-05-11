all: postc bc_to_post
postc: main.cpp
	g++ -o $@ -O3 -Wall -Wextra -std=c++17 $^

bin_to_post: bin_to_post.cpp
	g++ -o $@ -O3 -Wall -Wextra -std=c++17 $^
