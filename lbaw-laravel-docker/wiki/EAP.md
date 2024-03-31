# EAP: Architecture Specification and Prototype

> QueryStack is a platform for technology enthusiasts, professionals, and learners to share their knowledge and solve their problems. QueryStack allows users to ask, answer, vote, comment, and edit questions and answers related to various topics in technology, such as programming languages, frameworks, tools, algorithms, data structures, design patterns, etc. QueryStack also provides features such as tags, badges, reputation points, and leaderboards to categorize, reward, and rank the users and their contributions.

## A7: Web Resources Specification

> In this artifact we are going to present the architecture of the web API we are going to develop, with the resources needed.

### 1. Overview

> Identify and overview the modules that will be part of the application.  

| Module | Description |
| ------ | ----------- |
| M01: Authentication and Individual Profile| Web resources associated with user authentication and individual profile management. Includes the following system features: login/logout, register, edit profile, view profile, delete profile, view user´s comments and questions|
| M02: Questions| Web resources associated with questions. Includes the following system features: create question, edit question, delete question, view question, view all questions.|
|M03: Answers and Comments| web resources associated with answers and comments. Includes the following system features: create answer, edit answer, delete answer, view answer, create comment, edit comment, delete comment, view comment.|
| M04: Votes| Web resources associated with votes. Includes the following system features: vote question, vote answer, unvote question, unvote answer.|
| M05: Static pages| Web resources associated with static pages, about and contacts|
| M06: User administration and Moderation area| Web resources associated with administrators. Includes the following features: manage tags, assign moderator, remove moderator and manage members. . Web resources associated with moderators. Includes the following features: delete content (questions, answers and comments), edit question tags, manage reports and ban or block members.|


### 2. Permissions

> This section describes the permissions used in the last section.  

| Permission | Name | Description |
| ---------- | ---- | ----------- |
| PUB | Public| User without privileges|
| MEM | Member| Authenticated user|
| OWN | Owner| User who owns the content (question, comment and answer)|
| MOD | Moderator| User with moderator privileges|
| ADM | Administrator| User with administrator privileges|



### 3. OpenAPI Specification

> OpenAPI specification in YAML format to describe the vertical prototype's web resources.

> [Link to Open API](https://git.fe.up.pt/lbaw/lbaw2324/lbaw2311/-/blob/main/A7_OPENAPI.yaml?ref_type=heads)


```yaml
openapi: 3.0.0


info:
  version: 1.0.0
  title: 'QueryStack Web API'
  description: 'Web Resources Specification (A7) for QueryStack'

servers:
- url: http://http://lbaw2311.lbaw.fe.up.pt
  description: Production server


tags:
 - name: 'M01: Authentication and Individual Profile'
 - name: 'M02: Questions'
 - name: 'M03: Answers and Comments'
 - name: 'M04: Votes'
 - name: 'M05: Static pages'
 - name: 'M06: User Administration, Moderation'


paths:
  /login:
    get:
      operationId: R101
      summary: 'R101: Login Form'
      description: 'Provide login form. Access: PUB'
      tags:
        - 'M01: Authentication and Individual Profile'
      responses:
          '200':
            description: 'OK. Show login UI'
            
    post:
      operationId: R102
      summary: 'R102: Login Action'
      description: 'Login form submission. Access: PUB'
      tags:
        - 'M01: Authentication and Individual Profile'        
    
      requestBody:
        required: true
        content:
          application/x-www-form-urlencoded:
            schema:
              type: object
              properties:
                email:          
                  type: string
                  format: email
                password:    
                  type: string
                  format: password
              required:
                - email
                - password
 
      responses:
        '302':
          description: 'Redirect after processing the login credentials.'
          headers:
            Location:
              schema:
                type: string
              examples:
                302Success:
                  description: 'Authentication successful. Redirect to user profile.'
                  value: '/users/{id}'
                302Error:
                  description: 'Authentication failed. Redirect to login form.'
                  value: '/login'
        
  /logout:
    post:
      operationId: R103
      summary: 'R103: Logout Action'
      description: 'Logout the authenticated user. Access: MEM, ADM, MOD'
      tags:
        - 'M01: Authentication and Individual Profile'
      responses:
        '302':
          description: 'Redirect after processing logout.'
          headers:
            Location:
              schema:
                type: string
              examples:
                302Success:
                  description: 'Logout successful. Redirect to login form.'
                  value: '/login'
  /register:
    get:
      operationId: R104
      summary: 'R104: Register Form'
      description: 'Provide new user registration form. Access: PUB'
      tags:
        - 'M01: Authentication and Individual Profile'
      responses:
        '200':
          description: 'Ok. Show sign-up UI'

    post:
      operationId: R105
      summary: 'R105: Register Action'
      description: 'Processes the new user registration form submission. Access: PUB'
      tags:
        - 'M01: Authentication and Individual Profile'

      requestBody:
        required: true
        content:
          application/x-www-form-urlencoded:
            schema:
              type: object
              properties:
                username:
                  type: string
                email:
                  type: string
                  format: email
                password:
                  type: string
                  format: password
                birthDate:
                  type: string
                  format: date
                picture:
                  type: string
                  format: binary
              required:
                  - username
                  - email
                  - password
                  - birthDate

      responses:
        '302':
          description: 'Redirect after processing the new user information.'
          headers:
            Location:
              schema:
                type: string
              examples:
                302Success:
                  description: 'Successful authentication. Redirect to user profile.'
                  value: '/users/{id}'
                302Failure:
                  description: 'Failed authentication. Redirect to login form.'
                  value: '/login'
  /member/{id}:
  
    parameters:
        - in: path
          name: id
          schema:
            type: integer
          required: true  
    get:
      operationId: R106
      summary: 'R106: View user profile'
      description: 'Show the individual user profile. Access: MEM, OWN, MOD, ADM'
      tags:
        - 'M01: Authentication and Individual Profile'
        
      responses:
        '200':
          description: 'Ok. Show User Profile UI'
        '401':
          description: 'Not logged-in.'
        '404':
          description: 'User not found'
          
  /member/{id}/edit:
  
    parameters:
      - in: path
        name: id
        schema:
          type: integer
        required: true

    get:
      operationId: R107
      summary: 'R107: User profile edit form'
      description: 'Show the user edit profile page. Access: OWN'
      tags:
        - 'M01: Authentication and Individual Profile'

      responses:
        '200':
          description: 'Ok. Show User Profile UI'
        '401':
          description: 'Not logged-in.'
        '404':
          description: 'User not found'
    post:
      operationId: R108
      summary: 'R108: Edit user profile action'
      description: 'Edit user profile. Access: OWN'
      tags:
        - 'M01: Authentication and Individual Profile'
      parameters: 
        - in: path
          name: id
          schema:
            type: integer
          required: true
      requestBody:
        required: true
        content: 
          application/x-www-form-urlencoded:
            schema:
               type: object
               properties:
                username:
                  type: string
                email:
                  type: string
                  format: email
                password:
                  type: string
                  format: password
                birthDate:
                  type: string
                  format: date
                picture:
                  type: string
                  format: binary
      responses:
        '200':
          description: 'Ok. User profile updated'
        '401':
              description: 'Not logged-in.'  
        '404':
              description: 'User not found.'  
    delete:
      operationId: R109
      summary: 'R109: Delete user profile'
      description: 'Delete an user account. Acess: OWN, ADM'
      tags:
        - 'M01: Authentication and Individual Profile'
        
      parameters:
        - in: path
          name: id
          schema:
            type: integer
          required: true  
      responses:
        '200':
          description: 'Ok. User deleted.'
        '401':
          description: 'Not logged-in.'
        '404':
          description: 'User not found.'
  /questions/create:
    get: 
        operationId: R201
        summary: 'R201: Question Form'
        description: 'Provide a question form. Access: MEM'
        tags:
          - 'M02: Questions'
        responses:
          '200':
            description: 'Show the question form'
          '401':
            description: 'Not logged in'
                  
          
    post:
      operationId: R202
      summary: 'R202: Question Action'
      description: 'Question Form submission. Access:MEM'
      tags: 
        - 'M02: Questions'
        
      requestBody:
        required: true
        content:
          application/x-www-form-urlencoded:
            schema:
              type: object
              properties:
                question_title:
                  type: string
                  format: question_title
                content_text:
                  type: string
                  format: content_text
              required: 
                - title
                - content
      responses:
        '201':
          description: 'Redirect after processing question form.'
          headers:
            Location:
              schema:
                type: string
              examples:
                201Success:
                  description: 'Question created successfully. Redirect to question'
                  value: '/question/{id}'
                201Error:
                  description: 'Question creation failed. Redirect to question form.'
                  value: '/question'
        '401':
          description: 'Not logged in'
        
    
  /questions/{question_id}:
    parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true
    get:
      operationId: R203
      summary: 'R203: Get Question by ID'
      description: 'Retrieve a question by a scpecific ID'
      tags: 
        - 'M02: Questions'
      responses:
        '200':
          description: 'OK. Show Question'
        '404':
          description: 'Question not found'
          
  /questions/{question_id}/edit:
    parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true
        
    get:
      operationId: R204
      summary: 'R204: Question edit form'
      description: 'Show the question edit page. Access: OWN'
      tags: 
        - 'M02: Questions'
        
      responses:
        '200':
          description: 'OK. Show question form UI'
        '401':
          description: 'Not the owner'
          
    post:
      operationId: R205
      summary: 'R205: Edit question action'
      description: 'Edit question. Access:OWN'
      tags: 
        - 'M02: Questions'
      parameters: 
        - in: path
          name: question_id
          schema:
            type: integer
          required: true
      requestBody:
        required: true
        content:
          application/x-www-form-urlencoded:
            schema:
              type: object
              properties:
                question_title:
                  type: string
                  format: title
                content_text:
                  type: string
                  format: content
                  
      responses:
        '200':
          description: 'OK. Question updated'
        '401':
          description: 'Question not found'
        '404':
          description: 'User not found'
    
  /question/{question_id}:
    parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true
    delete:
      operationId: R206
      summary: 'R206: Delete question'
      description: 'Delete question. Access: OWN, MOD'
      tags: 
        - 'M02: Questions'
        
      
      responses:
        '200':
          description: 'OK. Question deleted'
        '401':
          description: 'Not logged in'
        '402':
          description: 'Question not found'
        '404':
          description: 'User not found'
          
          
  /questions:
    get:
      operationId: R207
      summary: 'R207: Get Questions'
      description: 'Retrieve a list of questions. Access: PUB'
      tags: 
        - 'M02: Questions'
      responses:
        '200':
          description: 'OK. Questions retrieved.'
          content:
            application/x-www-form-urlencoded:
              schema:
                type: object
                properties:
                  question_id:
                    type: integer
                  question_title:
                    type: string
                  content_text:
                    type: string
                  content_creation_date:
                    type: integer
                  content_is_edited:
                    type: boolean
                example: 
                  - question_id: 1
                    question_title: programming language
                    content_text: What is the best programming language
                    content_creation_date: 1698855459
                    content_is_edited: false
        '400':
          description: 'Bad Request'        

  /questions/{question_id}/answers/{answer_id}:
   get:
    operationId: R301
    summary: 'R301: Get Answer by ID'
    description: 'Retrieve an Answer by a specific ID'
    tags: 
      - 'M03: Answers and Comments'
    parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true
      - in: path
        name: answer_id
        schema:
          type: integer
        required: true

    responses:
        '200':
          description: 'OK. Show Answer'
        '404':
          description: 'Answer not found'

   delete:
      operationId: R302
      summary: 'R302: Delete answer'
      description: 'Delete answer. Access: OWN, MOD'
      tags: 
        - 'M03: Answers and Comments'
      parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true
      - in: path
        name: answer_id
        schema:
          type: integer
        required: true
      
      responses:
        '200':
          description: 'OK. Answer deleted'
        '401':
          description: 'Not logged in'
        '402':
          description: 'Answer not found'
        '404':
          description: 'User not found'

  /questions/{question_id}answers/{answer_id}/edit:
    parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true
      - in: path
        name: answer_id
        schema:
          type: integer
        required: true
        
    get:
      operationId: R303
      summary: 'R303: Answer edit form'
      description: 'Show the answer edit form. Access: OWN'
      tags: 
        - 'M03: Answers and Comments'
        
      responses:
        '200':
          description: 'OK. Show answer form UI'
        '401':
          description: 'Not the owner'
          
    post:
      operationId: R304
      summary: 'R304: Edit answer action'
      description: 'Edit answer. Access:OWN'
      tags: 
        - 'M03: Answers and Comments'
      parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true
      - in: path
        name: answer_id
        schema:
          type: integer
        required: true
      requestBody:
        required: true
        content:
          application/x-www-form-urlencoded:
            schema:
              type: object
              properties:
                content_text:
                  type: string
                  format: content_text
                  
      responses:
        '200':
          description: 'OK. Answer updated'
        '401':
          description: 'Answer not found'
        '404':
          description: 'User not found'
          
  /questions/{question_id}/answers:
   get:
    operationId: R305
    summary: 'R305:Create answer'
    description: 'Create an answer to some question'
    tags: 
      - 'M03: Answers and Comments'
    parameters:
      - in: path
        name: question_id
        schema:
          type: integer
        required: true

    responses:
        '200':
          description: 'OK. Answer created'
        '401':
          description: 'Not logged in'    
  /about:
    get:
      operationId: R501
      summary: 'R501: about page'
      description: 'Provide about page. ACCESS: PUB'
      tags:
        - 'M05: Static pages'
      responses:
        '200':
          description: 'OK. Show about page'
    
    
  /admin/assign:
    get:
      operationId: R601
      summary: 'R601: assign moderator form'
      description: 'Provide assign moderator form. ACCESS: ADM'
      tags: 
      - 'M06: User Administration, Moderation'
      responses:
        '200':
          description: 'OK. Show assign UI'
    post:
      operationId: R602
      summary: 'R602: assign moderator action'
      description: 'Assign moderator submission. ACCESS: ADM'
      tags: 
        - 'M06: User Administration, Moderation'
        
      requestBody:
        required: true
        content:
          application/x-www-form-urlencoded:
            schema:
              type: object
              properties:
                user:
                  type: string
                  format: user
                tag:
                  type: integer
                  format: tag
              required: 
                - user
                - tag
      responses:
        '200':
          description: 'Ok. Assignement done'
        '401':
          description: 'Not an admin.'  
        '404':
          description: 'User not found.'
                  
  /admin/remove:
    get:
      operationId: R603
      summary: 'R603: remove moderator form'
      description: 'Provide remove moderator form. ACCESS: ADM'
      tags: 
      - 'M06: User Administration, Moderation'
      responses:
        '200':
          description: 'OK. Show remove UI'
    post:
      operationId: R604
      summary: 'R604: remove moderator action'
      description: 'Remove moderator submission. ACCESS: ADM'
      tags: 
        - 'M06: User Administration, Moderation'
        
      requestBody:
        required: true
        content:
          application/x-www-form-urlencoded:
            schema:
              type: object
              properties:
                user:
                  type: string
                  format: user
              required: 
                - user
      responses:
        '200':
          description: 'Ok. Moderator removed.'
        '401':
          description: 'Not an admin.'  
        '404':
          description: 'User not found.'


```


## A8: Vertical prototype

> the vertical prototype of the application has all features marked with an asterisk (*) in the common and theme requirements implemented. 
We aimed to implement as much user stories as we could to validate our architecture. 

### 1. Implemented Features

#### 1.1. Implemented User Stories

> Identify the user stories that were implemented in the prototype.  

| User Story reference | Name                   | Priority                   | Description                   |
| -------------------- | ---------------------- | -------------------------- | ----------------------------- |
| US01                 | Sign-in | High | AS a visitor, I want to log into the system, so that I can access all the information and participate in discussions. |
| US02 | Sign-up | High | As a Visitor, I want to register into the system, so that later I can authenticate into the system. |
| US11 | Home Page | High | As a user, I want to access the home page so that I can see the top and newest questions.|
| US12 | Search | High | As a user, I want to search questions so that I can access the content I want|
| US14 | About Page | High | As a User, I want to access the about page so that I can see a detailed description of the website.|
| US15 | Contacts Page | High | As a User, I want to access the contacts page so that I can communicate with the platform creators.|
| US13 | Filter | High | As a user, I want to filter my search so that I can have a more efficiente and faster search|
| US201 | Post Question | High | As a member, I want to post a question so that people answer it and I can be clarified in some subject.|
| US202 | Post Answer | High | As a member, I want to answer a question so that I can share my thoughts about that question.|
| US205 | Personal Feed | High | As a member, I want to access my personal feed so that I can see information about the topics I am more interested about.|
| US207 | Log out | High | As a Member, I want to log out so that I don’t keep my account open on the browser.|
| US208 | Edit Profile | High | As a Member, I want to edit my profile so that I keep it updated or delete it.|
| US209 | Delete Account | High | As a Member, I want to delete my account so that no personal information remains in the platform.|
| US31 | Edit Question | High | AS an Author, I want to edit a question so that I can correct or reformulate it. |
| US32 | Delete Question | High | As an Author, I want to delete a question so that it won't be visible to anybody.|
| US33 | Edit Answer | High | As an Author, I want to edit an answer so that I can correct my own answer.|
| US34 | Delete Answer | High | As an Author, I want to delete an answer so that anybody can see it anymore.|
| US52 | Assign Moderator | High | As an Administrator I want to assign a moderator so that he has Moderator powers.|
| US53 | Remove Moderator | High | As an Administrator I want to remove a Moderator so that he no longer has Moderator powers.|





#### 1.2. Implemented Web Resources

> Identify the web resources that were implemented in the prototype.  

> Module M01: Authentication and Individual profile  

| Web Resource Reference | URL                            |
| ---------------------- | ------------------------------ |
| R101: Login Form | GET/login |
| R102: Login Action | POST/login |
| R103: Logout Action | POST/logout |
| R104: Register Form | GET/register |
| R105: Register Action | POST/register |
| R106: View user profile | GET/member/{id} |
| R107: User profile edit form | GET/member/{id}/edit |
| R108: User profile edit action | POST/member/{id}/edit |
| R109: User profile delete action | POST/member/{id}/delete |
| R110: Get user questions | GET/member/{id}/questions |
| R111: Get user answers | GET/member/{id}/answers |



> Module M02: Question 

| Web Resource Reference | URL                            |
| ---------------------- | ------------------------------ |
| R201: Question form | GET/questions/create|
| R202: Question action | POST/questions/create|
| R203: Get question by id | GET/questions/{question_id}|
| R204: Question edit form | GET/questions/{question_id}/edit|
| R205: Question edit action | POST/questions/{question_id}/edit|
| R206: Question delete | DELETE/question/{question_id}|
| R207: Get all questions | GET/questions|


> Module M03: Answers and commentws  

| Web Resource Reference | URL                            |
| ---------------------- | ------------------------------ |
| R301: Get answer by id | GET/questions/{question_id}/answers/{answer_id}|
| R302: Delete answer | DELETE/questions/{question_id}/answers/{answer_id}|
| R303: Answer edit form | GET/questions/{question_id}/answers/{answer_id}/edit|
| R304: Answer edit action | POST/questions/{question_id}/answers/{answer_id}/edit|
| R305: Create answer | POST/questions/{question_id}/answers|



> Module M05: Static pages

| Web Resource Reference | URL                            |
| ---------------------- | ------------------------------ |
| R501: About | GET/about|




> Module M06: User administration and Moderation area

| Web Resource Reference | URL                            |
| ---------------------- | ------------------------------ |
| R601: Assign moderator form | GET/admin/assign|
| R602: Assign moderator action | POST/admin/assign|
| R603: Remove moderator form | GET/admin/remove|
| R604: Remove moderator action | POST/admin/remove|


### 2. Prototype

> In this part of our wiki you can find the link to test our prototype as well as the credentials necessary in order to have access.


> The prototype is available at [https://lbaw2311.lbaw.fe.up.pt](https://lbaw2311.lbaw.fe.up.pt) (FEUP's VPN needed).  

> Users credentials

| Email | Password | Role|
| ---------- | ---------- | ---------- |
| member1@example.com| pass | member|
| moderator@example.com| pass | moderator|
| admin@example.com | pass | admin|

---



> High Priority User Stories implementation status

| US Reference | Description | Implementation Status |
|----------|----------|----------|
| US01 | Sign-in | Done |
| US02 | Sign-up | Done |
| US11 | Home Page | Done |
| US12 | Search | Done |
| US13 | Filter | To be implemented |
| US14 | About Page | Done |
| US15 | Contacts Page | Done |
| US16 | Personal scoreboard and badges | To be implemented |
| US17 | View scoreboards and badges | To be implemented |
| US201 | Post Question | Done |
| US202 | Post Answer | Done |
| US203 | Post comment | To be implemented |
| US204 | Rate/Vote | To be implemented |
| US205 | Personal Feed | To be implemented |
| US206 | Follow | To be implemented |
| US207 | Log out |Done |
| US208 | Edit profile | Done |
| US209 | Delete account | Done |
| US31 | Edit question | Done |
| US32 | Delete question | Done |
| US33 | Edit answer | Done |
| US34 | Delete answer | Done |
| US35 | Edit comment | To be implemented |
| US36 | Delete comment | To be implemented |
| US41 | Delete content | To be implemented |
| US42 | Edit question tags | To be implemented |
| US43 | Manage reports | To be implemented |
| US51 | Manage tags | To be implemented |
| US52 | Assign moderator | Done |
| US53 | Remove moderator | Done |
| US54 | Manage members | To be implemented |






## Revision history

Changes made to the first submission:
1. None

***
GROUP2311, 20/11/2023
 
* António José Salazar Correia, up201804832@up.pt
* Gonçalo Nuno Leitão Pinho da Costa, up202103336@up.pt (Editor)
* Tomás Pereira Maciel, up202006845@up.pt 
* Ricardo Miguel Matos Oliveira Peralta, up202206392@up.pt