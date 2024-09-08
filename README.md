# Social-Web

**Social Network Graph**


A simple social network application implemented in C++.
This program allows users to create accounts, follow others, view followers and following lists, and manage their bio data.
It uses a graph-based structure to manage user relationships and interactions.

**Features**
- **Create and Manage Accounts:** Users can create new accounts and update their bio data including Date of Birth (DOB), institution, and native place.
- **Follow and Unfollow:** Users can follow other users and view their followers and following lists.
- **View Bio Data:** Users can view their own bio data and update it as needed.
- **View Connections:** Users can see who they follow and who follows them, as well as people they don't follow back and who don't follow them back.
- **Search for Users:** Users can search for other users and view their bio data, as well as check if they follow the user or if the user follows them.
  
**Classes**
- 'Vertex': Represents a user in the social network with attributes for user ID, name, password, and bio data.
  It also contains pointers for edges (followers) and other vertices (connections).
- 'Edge': Represents the relationship between users, storing the ID and username of the user being followed and a link to the next edge.
- 'Biodata': Stores additional user information such as DOB, institution, and native place.
- 'Graph': Manages the entire social network, including user accounts, relationships, and various operations like following users and viewing connections.
**Usage**
- **Running the Program:** Compile and run the program using a C++ compiler.
- **Creating an Account:** Choose the option to create a new account and follow the prompts to enter user details and bio data.
- **Logging In:** Use the login option to access an existing account by providing the user ID and password.
- **Interacting:** After logging in, you can follow other users, view followers, view people you may know, and update your bio data.
