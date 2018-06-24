/*

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
   
*/
   


/*

DP Solution
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
public:
	vector<TreeNode*> doGenTree( int begin, int end )
	{
		vector<TreeNode*> ret;
		if( begin > end )
		{
            ret.push_back(nullptr);
			return ret;
		}
		if( begin == end )
		{
            cout<< "pushing: "<<begin<<endl;
			ret.push_back( new TreeNode(begin) );
		}
		else
		{
			for( int mid = begin; mid <= end; mid++ )
			{
				auto leftNodes = doGenTree(begin, mid-1);
				auto rightNodes = doGenTree(mid+1, end);

				for( const auto ln : leftNodes )
				{
					for( const auto rn : rightNodes )
					{
                        cout<<mid<<endl;
						TreeNode* newP = new TreeNode(mid);
                        if (ln)
                            cout<<"left: "<<ln->val<<endl;
                        if (rn)
                            cout<<"right: "<<rn->val<<endl;
						newP->left = ln;
						newP->right = rn;
						ret.push_back(newP);
					}
                    cout<<"done"<<endl;
				}
			}
		}

		return ret;
	}

    vector<TreeNode*> generateTrees(int n) {
    	return doGenTree(1, n);
    }
};

Debugging:

pushing: 3
2
right: 3
done
pushing: 2
3
left: 2
done
1
right: 2
1
right: 3
done
pushing: 1
pushing: 3
2
left: 1
right: 3
done
pushing: 2
1
right: 2
done
pushing: 1
2
left: 1
done
3
left: 1
done
3
left: 2
done
   
