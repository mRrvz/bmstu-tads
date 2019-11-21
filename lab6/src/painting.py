from tkinter import *
import argparse

CANVAS_WIDHT = 1000
CANVAS_HEIGHT = 1000
HEIGHT = 25
RL_COEFF = 20
TB_COEFF = 20
START_TREE_Y = 17
RL_STEP = 100
TB_STEP = 100

parser = argparse.ArgumentParser()
parser.add_argument('tree', type=str)
args = parser.parse_args()

def draw_tree():
    tree_branches = args.tree.split('_')
    first_branch = tree_branches[0].split()
    tree_vertex = []

    root = Tk()
    c = Canvas(root, width=CANVAS_WIDHT, height=CANVAS_HEIGHT, bg='white')

    c.create_oval(
        [CANVAS_WIDHT / 2, START_TREE_Y],
        [CANVAS_HEIGHT / 2 + HEIGHT, HEIGHT + START_TREE_Y],
        fill="pink"
    )

    c.create_text(
        CANVAS_WIDHT / 2 + HEIGHT / 2,
        START_TREE_Y - HEIGHT / 2,
        text=first_branch[0],
        font="Arial 7"
    )

    tree_vertex.append((
        first_branch[0], (
            CANVAS_WIDHT / 2,
            HEIGHT / 5,
            CANVAS_HEIGHT / 2 + HEIGHT,
            HEIGHT
            )
        )
    )

    for i in range(len(tree_branches)):
        RL_STEP = 100
        TB_STEP = 100
        current_branch = list(map(str, tree_branches[i].split()))
        for j in range(len(tree_vertex)):
            if (tree_vertex[j][0] == current_branch[0]):
                RL_STEP -= RL_COEFF * int(current_branch[3])
                TB_STEP += TB_COEFF * int(current_branch[3])

                if (current_branch[1] != "NULL"):
                    c.create_oval(
                        [tree_vertex[j][1][0] - RL_STEP, tree_vertex[j][1][1] + TB_STEP],
                        [tree_vertex[j][1][2] - RL_STEP, tree_vertex[j][1][3] + TB_STEP],
                        fill="pink"
                    )

                    c.create_line(
                        tree_vertex[j][1][0] + HEIGHT / 2,
                        tree_vertex[j][1][1] + HEIGHT / 2,
                        tree_vertex[j][1][0] - RL_STEP + HEIGHT / 2,
                        tree_vertex[j][1][1] + TB_STEP + HEIGHT / 2
                    )

                    c.create_text(
                        tree_vertex[j][1][0] - RL_STEP + HEIGHT / 2,
                        tree_vertex[j][1][1] + TB_STEP - HEIGHT / 2,
                        text=current_branch[1],
                        font="Arial 7"
                    )

                    tree_vertex.append((
                        current_branch[1], (
                            tree_vertex[j][1][0] - RL_STEP,
                            tree_vertex[j][1][1] + TB_STEP,
                            tree_vertex[j][1][2] - RL_STEP,
                            tree_vertex[j][1][3] + TB_STEP
                            )
                        )
                    )

                if (current_branch[2] != "NULL"):
                    c.create_oval(
                        [tree_vertex[j][1][0] + RL_STEP, tree_vertex[j][1][1] + TB_STEP],
                        [tree_vertex[j][1][2] + RL_STEP, tree_vertex[j][1][3] + TB_STEP],
                        fill="pink"
                    )

                    c.create_line(
                        tree_vertex[j][1][0] + HEIGHT / 2,
                        tree_vertex[j][1][1] + HEIGHT / 2,
                        tree_vertex[j][1][0] + RL_STEP + HEIGHT / 2,
                        tree_vertex[j][1][1] + TB_STEP + HEIGHT / 2
                    )

                    c.create_text(
                        tree_vertex[j][1][0] + RL_STEP + HEIGHT / 2,
                        tree_vertex[j][1][1] + TB_STEP - HEIGHT / 2,
                        text=current_branch[2],
                        font="Arial 7"
                    )

                    tree_vertex.append((
                        current_branch[2], (
                            tree_vertex[j][1][0] + RL_STEP,
                            tree_vertex[j][1][1] + TB_STEP,
                            tree_vertex[j][1][2] + RL_STEP,
                            tree_vertex[j][1][3] + TB_STEP
                            )
                        )
                    )

                break


    c.pack()
    root.mainloop()

if __name__ == "__main__":
    draw_tree()
