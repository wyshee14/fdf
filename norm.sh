#!/bin/bash

echo "----- check include -----"
norminette include/
echo -e "\n----- check libft -----"
norminette libft/
echo -e "\n----- check src -----"
norminette src/
