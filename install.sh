clang++ msrcs.cpp --std=c++98 -Wall -Wextra -Werror -o msrcs
cp msrcs ~/.msrcs
echo "alias msrcs='~/.msrcs'" >> ~/.bashrc
echo "alias msrcs='~/.msrcs'" >> ~/.zshrc
