# Relational Algebra Query Application

Created as the final project for my Object-Oriented Programming class at CTU.

The application enables users to perform database queries using relational algebra, making simpler and more straightforward queries. Users have the option to connect to PostgreSQL databases or load CSV files from a chosen folder. The input processing employs polymorphism, abstracting operations like data loading, table creation, and row storage. Query results can be written to new CSV files, benefiting from polymorphism features.

Users can input queries repeatedly and exit as needed, with access to helpful prompts throughout the program. The allowed query syntax can be found in `povolene_dotazy.txt`. Query processing and evaluation utilize a polymorphic parsing tree, which allows constructing a tree with nodes reacting differently to specific methods. The tree facilitates branching and gradual evaluation of queries, all simplified with the use of polymorphism.

Polymorphism is harnessed for various connection types (natural join, generic join), complex queries, and set operations (union, intersection). Query results can be stored and used in subsequent queries.

Finally, users can convert their input expression into SQL.

## Program Structure

- Data Input
    - CSV
        - Import
        - Export
    - Database Connection

- User Input
    - Interface (providing basic usage info, allowed queries, menu)
    - Tokenizer
    - Parser
    - Expression
        - Binary Expression
            - Join Expression (performing join between two tables)
                - Generic Join
                - Natural Join
            - Set Expression (performing set operations)
                - Union
                - Intersect
                - Difference
        - Cartesian Product
        - Table Expression (table selection for processing)
        - Projection Expression

## ALLOWED QUERIES

Users can input queries repeatedly and exit as needed, with access to helpful prompts throughout the program. The allowed query syntax is as follows:

### SELECTION

{TABLE(WHERE = 'attribute'...)}

### PROJECTION

{TABLE(WHERE = 'attribute'...)} [column1, column2, ..., columnN-1, columnN]

### RENAMING

{TABLE(WHERE = 'attribute'...)...} [column -> [rename]..]

### JOIN

- RIGHT JOIN

{TABLE(WHERE = 'attribute'...)} >* {TABLE(WHERE = 'attribute'...)} [column1, column2, ..., columnN-1, columnN]

- LEFT JOIN

{TABLE(WHERE = 'attribute'...)} <* {TABLE(WHERE = 'attribute'...)} [column1, column2, ..., columnN-1, columnN]

- NATURAL JOIN

{TABLE(WHERE = 'attribute'...)} * {TABLE(WHERE = 'attribute'...)} [column1, column2, ..., columnN-1, columnN]

- JOIN ON

{TABLE1(WHERE = 'attribute'...) [TABLE1.ATTRIBUTE=TABLE2.ATTRIBUTE] TABLE1(WHERE = 'attribute'...)} [column1, column2, ..., columnN-1, columnN]

### ANTIJOIN

- ANTI LEFT JOIN

{TABLE(WHERE = 'attribute'...)} !< {TABLE(WHERE = 'attribute'...)} [column1, column2, ..., columnN-1, columnN]

- ANTI RIGHT JOIN

{TABLE(WHERE = 'attribute'...)} >! {TABLE(WHERE = 'attribute'...)} [column1, column2, ..., columnN-1, columnN]

### SET OPERATIONS

- UNION

{QUERY1} ⋃ {QUERY2} ⋃ ...⋃ {QUERYn-1} ⋃ {QUERYn}

- INTERSECTION

{QUERY1} ⋂ {QUERY2} ⋂ ...⋂ {QUERYn-1} ⋂ {QUERYn}

- DIFFERENCE

{QUERY1} \ {QUERY2} \ ... \ {QUERYn-1} \ {QUERYn}

- CARTESIAN PRODUCT

{QUERY1} × {QUERY2} × ...× {QUERYn-1} × {QUERYn}

### AGGREGATE FUNCTIONS

- PROJECTION (with Aggregation)

{TABLE(WHERE = 'attribute'...)} [column1 -> AGGREGATE FUNCTION, column2, ..., columnN-1, columnN]

- MATH FUNCTIONS

    - AVERAGE: Computes the average value of the specified column
      {TABLE(WHERE = 'attribute'...)} [column1 -> AVERAGE]

    - GREATER THAN (GT) AVERAGE: Selects data greater than the average value of the specified column
      {TABLE(WHERE = 'attribute'...)} [column1 > AVERAGE]

    - SUM: Computes the count of data matching the query
      SUM {TABLE(WHERE = 'attribute'...)...} [column1, column2, ..., columnN-1, columnN] translated as well

- Each subquery must be correctly enclosed in curly brackets.
- Commas and semicolons must be included where required, both for specifying sought attributes and column names; otherwise, the query will be evaluated as incorrect.
