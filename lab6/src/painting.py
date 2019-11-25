from tkinter import *
import argparse

CANVAS_WIDHT = 1600
CANVAS_HEIGHT = 1600
HEIGHT = 20
RL_COEFF = 20
TB_COEFF = 30
S_CONF = 20
START_TREE_Y = 20

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
        font="Arial 10"
    )

    tree_vertex.append((
        first_branch[0], (
            CANVAS_WIDHT / 2,
            START_TREE_Y,
            CANVAS_HEIGHT / 2 + HEIGHT,
            HEIGHT + START_TREE_Y,
            (CANVAS_WIDHT / 2 + CANVAS_HEIGHT / 2 + HEIGHT) / 2
            )
        )
    )

    for i in range(len(tree_branches)):
        current_branch = list(map(str, tree_branches[i].split()))
        for j in range(len(tree_vertex)):
            if (tree_vertex[j][0] == current_branch[0]):
                RL_STEP = RL_COEFF * (int(current_branch[3]) + 1)
                TB_STEP = TB_COEFF * (int(current_branch[3]) + 1)

                if (current_branch[1] != "NULL"):
                    c.create_oval(
                        [tree_vertex[j][1][0] - RL_STEP - S_CONF, tree_vertex[j][1][1] + TB_STEP],
                        [tree_vertex[j][1][2] - RL_STEP - S_CONF, tree_vertex[j][1][3] + TB_STEP],
                        fill="pink"
                    )

                    c.create_line(
                        tree_vertex[j][1][4],
                        tree_vertex[j][1][1] + HEIGHT / 2,
                        tree_vertex[j][1][0] - RL_STEP + HEIGHT / 2 - S_CONF,
                        tree_vertex[j][1][1] + TB_STEP + HEIGHT / 2
                    )

                    c.create_text(
                        tree_vertex[j][1][0] - RL_STEP + HEIGHT / 2 - S_CONF,
                        tree_vertex[j][1][1] + TB_STEP - HEIGHT / 2,
                        text=current_branch[1],
                        font="Arial 10"
                    )

                    tree_vertex.append((
                        current_branch[1], (
                            tree_vertex[j][1][0] - RL_STEP,
                            tree_vertex[j][1][1] + TB_STEP,
                            tree_vertex[j][1][2] - RL_STEP,
                            tree_vertex[j][1][3] + TB_STEP,
                            ((tree_vertex[j][1][0] - RL_STEP - S_CONF) + (tree_vertex[j][1][2] - RL_STEP - S_CONF)) / 2
                            )
                        )
                    )

                if (current_branch[2] != "NULL"):
                    c.create_oval(
                        [tree_vertex[j][1][0] + RL_STEP + S_CONF, tree_vertex[j][1][1] + TB_STEP],
                        [tree_vertex[j][1][2] + RL_STEP + S_CONF, tree_vertex[j][1][3] + TB_STEP],
                        fill="pink"
                    )

                    c.create_line(
                        tree_vertex[j][1][4],
                        tree_vertex[j][1][1] + HEIGHT / 2,
                        tree_vertex[j][1][0] + RL_STEP + HEIGHT / 2 + S_CONF,
                        tree_vertex[j][1][1] + TB_STEP + HEIGHT / 2
                    )

                    c.create_text(
                        tree_vertex[j][1][0] + RL_STEP + HEIGHT / 2 + S_CONF,
                        tree_vertex[j][1][1] + TB_STEP - HEIGHT / 2,
                        text=current_branch[2],
                        font="Arial 10"
                    )

                    tree_vertex.append((
                        current_branch[2], (
                            tree_vertex[j][1][0] + RL_STEP,
                            tree_vertex[j][1][1] + TB_STEP,
                            tree_vertex[j][1][2] + RL_STEP,
                            tree_vertex[j][1][3] + TB_STEP,
                            (tree_vertex[j][1][0] + RL_STEP + S_CONF + tree_vertex[j][1][2] + RL_STEP + S_CONF) / 2
                            )
                        )
                    )

                break


    c.pack()
    root.mainloop()

if __name__ == "__main__":
    draw_tree()
