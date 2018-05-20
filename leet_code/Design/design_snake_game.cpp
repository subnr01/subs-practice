/*
Design a Snake game that is played on a device with screen size = width x height. Play the game online if you are not familiar with the game.

The snake is initially positioned at the top left corner (0,0) with length = 1 unit.

You are given a list of food's positions in row-column order. When a snake eats the food, its length and the game's score both increase by 1.

Each food appears one by one on the screen. For example, the second food will not appear until the first food was eaten by the snake.

When a food does appear on the screen, it is guaranteed that it will not appear on a block occupied by the snake.



*/
//https://discuss.leetcode.com/topic/48626/java-deque-and-hashset-design-with-detailed-comments
//https://discuss.leetcode.com/topic/47385/c-straightforward-solution

class SnakeGame {
public:
/** Initialize your data structure here.
@param width - screen width
@param height - screen height
@param food - A list of food positions
E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */

int w, h, pos;
vector<pair<int, int>> food;
set<pair<int, int>> hist;
deque<pair<int, int>> q;

SnakeGame(int width, int height, vector<pair<int, int>> food) {
	this->food = food;
	w = width, h = height, pos = 0;
	q.push_back(make_pair(0, 0));
}

/** Moves the snake.
@param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
@return The game's score after the move. Return -1 if game over.
Game over when snake crosses the screen boundary or bites its body. */
int move(string direction) {
	int row = q.back().first, col = q.back().second;
	pair<int, int> d = q.front(); q.pop_front();
	hist.erase(d);

	if (direction == "U")
		row--;
	else if (direction == "D")
		row++;
	else if (direction == "L")
		col--;
	else if (direction == "R")
		col++;

	if (row < 0 || col < 0 || col >= w || row >= h || hist.count(make_pair(row, col)))
		return -1;

	hist.insert(make_pair(row, col));
	q.push_back(make_pair(row, col));

	if (pos >= food.size())
		return q.size() - 1;

	if (row == food[pos].first && col == food[pos].second) {
		pos++;
		q.push_front(d);
		hist.insert(d);
	}

	return q.size() - 1;
  }
};
