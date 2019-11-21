from tkinter import *
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('tree', type=str)
args = parser.parse_args()
print(args.tree)
tree = args.tree.split('_')
print(tree)
tree_arr = []

root = Tk()
cs_width = 1000
cs_height = 1000
height = 25
start_tree_y = 17
rl_step = 100
tb_step = 100
first_branch = tree[0].split()
print(first_branch)
c = Canvas(root, width=cs_width, height=cs_height, bg='white')
c.create_oval([cs_width/2, start_tree_y],[cs_height/2 + height,height + start_tree_y],fill="pink")
c.create_text(cs_width / 2 + height / 2,start_tree_y - height / 2,text=first_branch[0],font="Arial 7")
tree_arr.append((first_branch[0], (cs_width / 2, 5, cs_height / 2 + height, height)))

c.create_oval([tree_arr[0][1][0] - rl_step, tree_arr[0][1][1] + tb_step],[tree_arr[0][1][2] - rl_step, tree_arr[0][1][3] +tb_step],fill="pink")
c.create_text(tree_arr[0][1][0] - rl_step + height / 2, tree_arr[0][1][1] + tb_step - height / 2, text=first_branch[1],font="Arial 7")
tree_arr.append((first_branch[1], (tree_arr[0][1][0] - rl_step, tree_arr[0][1][1] + tb_step, tree_arr[0][1][2] - rl_step, tree_arr[0][1][3] + tb_step)))

c.create_oval([tree_arr[0][1][0] + rl_step , tree_arr[0][1][1] + tb_step],[tree_arr[0][1][2] + rl_step, tree_arr[0][1][3] +tb_step],fill="pink")
c.create_text(tree_arr[0][1][0] + rl_step + height / 2, tree_arr[0][1][1] + tb_step - height / 2, text=first_branch[2],font="Arial 7")
tree_arr.append((first_branch[2], (tree_arr[0][1][0] + rl_step, tree_arr[0][1][1] + tb_step, tree_arr[0][1][2] + rl_step, tree_arr[0][1][3] + tb_step)))

j = 0
c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] - rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)
c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] + rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)


for i in range(1,len(tree)):
    rl_step = 100
    tb_step = 100
    current_branch = list(map(str, tree[i].split()))
    for j in range(len(tree_arr)):
        if (tree_arr[j][0] == current_branch[0]):
            rl_step = rl_step - 20 * int(current_branch[3])
            tb_step = tb_step + 20 * int(current_branch[3])
            if (current_branch[1] != "NULL"):
                c.create_oval([tree_arr[j][1][0] - rl_step, tree_arr[j][1][1] + tb_step],[tree_arr[j][1][2] - rl_step, tree_arr[j][1][3] +tb_step],fill="pink")
                c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] - rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)
                c.create_text(tree_arr[j][1][0] - rl_step + height / 2, tree_arr[j][1][1] + tb_step - height / 2, text=current_branch[1],font="Arial 7")

                tree_arr.append((current_branch[1], (tree_arr[j][1][0] - rl_step, tree_arr[j][1][1] + tb_step, tree_arr[j][1][2] - rl_step, tree_arr[j][1][3] + tb_step)))

            if (current_branch[2] != "NULL"):
                c.create_oval([tree_arr[j][1][0] + rl_step, tree_arr[j][1][1] + tb_step],[tree_arr[j][1][2] + rl_step, tree_arr[j][1][3] +tb_step],fill="pink")
                c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] + rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)
                c.create_text(tree_arr[j][1][0] + rl_step + height / 2, tree_arr[j][1][1] + tb_step - height / 2, text=current_branch[2],font="Arial 7")

                tree_arr.append((current_branch[2], (tree_arr[j][1][0] + rl_step, tree_arr[j][1][1] + tb_step, tree_arr[j][1][2] + rl_step, tree_arr[j][1][3] + tb_step)))

            break


c.pack()
root.mainloop()
