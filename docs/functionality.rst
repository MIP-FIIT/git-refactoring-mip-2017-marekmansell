Functionality
=================



.. c:function:: FILE* OpenRecords(FILE *file)

User input: ``v``

loads records from `INPUT_FILE` and prints them

``file``: pointer to main FILE object

returns `NULL` on error (if file could not be open), otherwise pointer to `FILE` object






.. c:function:: int EmployeeBonus(long current_date, FILE *file)

User input: ``o <yyyymmdd>``

Prints out the bonuses each employee should receive to the current date

``current_date``: int representation on current date

``file``:         pointer to main FILE object

returns: `0`



.. c:function:: int LoadLicencePlates(FILE *file, char **licence_plates)

User input: ``n``

loads records from `INPUT_FILE` and stores them into an array

``file``: pointer to main FILE object

``licence_plates``: pointer to licence plate array

returns: `0`


.. c:function:: int PrintLicencePlates(char *licence_plates)

User input: ``s``

prints all licence plates from memory in a `'XX 000 XX\n'` format

``licence_plates``: pointer to licence plates string

returns: `0`



.. c:function:: int PrintPalindromes(char *licence_plates)

User input: ``p``

prints all licence plates from memory which are palindomes in a 'XX\n' format

``licence_plates``: pointer to licence plates string

returns: `0`


.. c:function:: int BestSelling(char *licence_plates)

User input: ``z``

prints all best selling regions by licence plate in a 'XX <number>\n' format

``licence_plates``: pointer to licence plates string

returns `-1` when licence_plates were not loaded, otherwise `0`
