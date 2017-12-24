create or replace function common_prefix(text, text) 
    returns text AS 'text_utils.so', 'common_prefix' 
    LANGUAGE C STRICT;

create or replace function common_end(text, text) 
    returns text AS 'text_utils.so', 'common_end' 
    LANGUAGE C STRICT;

create or replace function diff_index(text, text) 
    returns integer AS 'text_utils.so', 'diff_index' 
    LANGUAGE C STRICT;

create or replace function count_matches(text, text) 
    returns integer AS 'text_utils.so', 'count_matches' 
    LANGUAGE C STRICT;