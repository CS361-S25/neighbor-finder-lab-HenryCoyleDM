#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/math.hpp"

emp::web::Document doc{"target"};

class NFAnimator : public emp::web::Animate {
    emp::web::Canvas canvas{800, 800, "canvas"};
    int focal_x;
    int focal_y;
    int width = 20;
    int height = 20;
    int cell_size = 40;

    public:
    NFAnimator() {
        doc << canvas;
        // find the neighbors of two example cells, one in the middle and one one the edge
        // FindNeighbors(6, 7);
        // FindNeighbors(0, 0);
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        focal_x = 0;
        focal_y = 0;
    }

    // draw the focal cell in black and its 8 neighbors in red
    public:
    void FindNeighbors(int x, int y) {
        for (int dx=-1; dx<=1; dx++) {
            for (int dy=-1; dy<=1; dy++) {
                int new_x = emp::Mod(x + dx, width);
                int new_y = emp::Mod(y + dy, height);
                if (dx == 0 && dy == 0) {
                    canvas.Rect(cell_size * new_x, cell_size * new_y, cell_size, cell_size, "black", "black");
                } else {
                    canvas.Rect(cell_size * new_x, cell_size * new_y, cell_size, cell_size, "red", "black");
                }
            }
        }
    }

    public:
    void DrawGrid() {
        for (int x=0; x<width; x++) {
            for (int y=0; y<height; y++) {
                canvas.Rect(cell_size * x, cell_size * y, cell_size, cell_size, "white", "black");
            }
        }
    }

    public:
    void DoFrame() override {
        canvas.Clear();
        DrawGrid();
        FindNeighbors(focal_x, focal_y);
        focal_x++;
        if (focal_x >= width) {
            focal_x = 0;
            focal_y++;
            if (focal_y >= height) {
                focal_y = 0;
            }
        }
    }
};

NFAnimator animator;

int main() {
    animator.Step();
}