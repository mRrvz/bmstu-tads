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
rl_step = 100
tb_step = 100
c = Canvas(root, width=cs_width, height=cs_height, bg='white')
c.create_oval([cs_width/2,5],[cs_height/2 + height,height],fill="pink")
tree_arr.append((1, (cs_width / 2, 5, cs_height / 2 + height, height)))

c.create_oval([tree_arr[0][1][0] - rl_step, tree_arr[0][1][1] + tb_step],[tree_arr[0][1][2] - rl_step, tree_arr[0][1][3] +tb_step],fill="pink")
tree_arr.append((2, (tree_arr[0][1][0] - rl_step, tree_arr[0][1][1] + tb_step, tree_arr[0][1][2] - rl_step, tree_arr[0][1][3] + tb_step)))

c.create_oval([tree_arr[0][1][0] + rl_step , tree_arr[0][1][1] + tb_step],[tree_arr[0][1][2] + rl_step, tree_arr[0][1][3] +tb_step],fill="pink")

tree_arr.append((3, (tree_arr[0][1][0] + rl_step, tree_arr[0][1][1] + tb_step, tree_arr[0][1][2] + rl_step, tree_arr[0][1][3] + tb_step)))

j = 0
c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] - rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)
c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] + rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)

print(tree_arr)

for i in range(1,len(tree)):
    rl_step = 100
    tb_step = 100
    current_branch = list(map(int, tree[i].split()))
    print(current_branch)
    for j in range(len(tree_arr)):
        if (tree_arr[j][0] == current_branch[0]):
            rl_step = rl_step - 20 * current_branch[3]
            tb_step = tb_step + 20 * current_branch[3]
            if (current_branch[1] != 0):
                c.create_oval([tree_arr[j][1][0] - rl_step, tree_arr[j][1][1] + tb_step],[tree_arr[j][1][2] - rl_step, tree_arr[j][1][3] +tb_step],fill="pink")
                c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] - rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)

                tree_arr.append((current_branch[1], (tree_arr[j][1][0] - rl_step, tree_arr[j][1][1] + tb_step, tree_arr[j][1][2] - rl_step, tree_arr[j][1][3] + tb_step)))

            if (current_branch[2] != 0):
                c.create_oval([tree_arr[j][1][0] + rl_step, tree_arr[j][1][1] + tb_step],[tree_arr[j][1][2] + rl_step, tree_arr[j][1][3] +tb_step],fill="pink")
                c.create_line(tree_arr[j][1][0] + height / 2, tree_arr[j][1][1] + height / 2, tree_arr[j][1][0] + rl_step + height / 2, tree_arr[j][1][1] + tb_step + height / 2)

                tree_arr.append((current_branch[2], (tree_arr[j][1][0] + rl_step, tree_arr[j][1][1] + tb_step, tree_arr[j][1][2] + rl_step, tree_arr[j][1][3] + tb_step)))

            break

            print(tree_arr)


c.pack()

#c.create_line(10, 10, 190, 50)

#c.create_line(100, 180, 100, 60, fill='green',
                #width=5, arrow=LAST, dash=(10,2),
                #activefill='lightgreen',
                #arrowshape="10 20 10")

root.mainloop()
