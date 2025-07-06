/*  new_york.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* This file gets included by tz.c to get default rules in the
   absence of a default rules file in TZDIR.  Its contents is
   pretty self-explanatory.  NOTE: It is STRONGLY recommended
   that you learn the contents of this file by heart!  */
static const struct state new_york =
{
  0,  /* leapcnt */
  236,  /* timecnt */
  8,  /* typecnt */
  20,  /* charcnt */
  0,  /* goback */
  0,  /* goahead */
  {  /* ats */
    -2147483647L - 1, /* Fri Dec 13 20:45:52 UTC 1901 */
    -1633280400L, /* Sun Mar 31 07:00:00 UTC 1918 */
    -1615140000L, /* Sun Oct 27 06:00:00 UTC 1918 */
    -1601830800L, /* Sun Mar 30 07:00:00 UTC 1919 */
    -1583690400L, /* Sun Oct 26 06:00:00 UTC 1919 */
    -1570381200L, /* Sun Mar 28 07:00:00 UTC 1920 */
    -1551636000L, /* Sun Oct 31 06:00:00 UTC 1920 */
    -1536512400L, /* Sun Apr 24 07:00:00 UTC 1921 */
    -1523210400L, /* Sun Sep 25 06:00:00 UTC 1921 */
    -1504458000L, /* Sun Apr 30 07:00:00 UTC 1922 */
    -1491760800L, /* Sun Sep 24 06:00:00 UTC 1922 */
    -1473008400L, /* Sun Apr 29 07:00:00 UTC 1923 */
    -1459706400L, /* Sun Sep 30 06:00:00 UTC 1923 */
    -1441558800L, /* Sun Apr 27 07:00:00 UTC 1924 */
    -1428256800L, /* Sun Sep 28 06:00:00 UTC 1924 */
    -1410109200L, /* Sun Apr 26 07:00:00 UTC 1925 */
    -1396807200L, /* Sun Sep 27 06:00:00 UTC 1925 */
    -1378659600L, /* Sun Apr 25 07:00:00 UTC 1926 */
    -1365357600L, /* Sun Sep 26 06:00:00 UTC 1926 */
    -1347210000L, /* Sun Apr 24 07:00:00 UTC 1927 */
    -1333908000L, /* Sun Sep 25 06:00:00 UTC 1927 */
    -1315155600L, /* Sun Apr 29 07:00:00 UTC 1928 */
    -1301853600L, /* Sun Sep 30 06:00:00 UTC 1928 */
    -1283706000L, /* Sun Apr 28 07:00:00 UTC 1929 */
    -1270404000L, /* Sun Sep 29 06:00:00 UTC 1929 */
    -1252256400L, /* Sun Apr 27 07:00:00 UTC 1930 */
    -1238954400L, /* Sun Sep 28 06:00:00 UTC 1930 */
    -1220806800L, /* Sun Apr 26 07:00:00 UTC 1931 */
    -1207504800L, /* Sun Sep 27 06:00:00 UTC 1931 */
    -1189357200L, /* Sun Apr 24 07:00:00 UTC 1932 */
    -1176055200L, /* Sun Sep 25 06:00:00 UTC 1932 */
    -1157302800L, /* Sun Apr 30 07:00:00 UTC 1933 */
    -1144605600L, /* Sun Sep 24 06:00:00 UTC 1933 */
    -1125853200L, /* Sun Apr 29 07:00:00 UTC 1934 */
    -1112551200L, /* Sun Sep 30 06:00:00 UTC 1934 */
    -1094403600L, /* Sun Apr 28 07:00:00 UTC 1935 */
    -1081101600L, /* Sun Sep 29 06:00:00 UTC 1935 */
    -1062954000L, /* Sun Apr 26 07:00:00 UTC 1936 */
    -1049652000L, /* Sun Sep 27 06:00:00 UTC 1936 */
    -1031504400L, /* Sun Apr 25 07:00:00 UTC 1937 */
    -1018202400L, /* Sun Sep 26 06:00:00 UTC 1937 */
    -1000054800L, /* Sun Apr 24 07:00:00 UTC 1938 */
    -986752800L, /* Sun Sep 25 06:00:00 UTC 1938 */
    -968000400L, /* Sun Apr 30 07:00:00 UTC 1939 */
    -955303200L, /* Sun Sep 24 06:00:00 UTC 1939 */
    -936550800L, /* Sun Apr 28 07:00:00 UTC 1940 */
    -923248800L, /* Sun Sep 29 06:00:00 UTC 1940 */
    -905101200L, /* Sun Apr 27 07:00:00 UTC 1941 */
    -891799200L, /* Sun Sep 28 06:00:00 UTC 1941 */
    -880218000L, /* Mon Feb  9 07:00:00 UTC 1942 */
    -769395600L, /* Tue Aug 14 23:00:00 UTC 1945 */
    -765396000L, /* Sun Sep 30 06:00:00 UTC 1945 */
    -747248400L, /* Sun Apr 28 07:00:00 UTC 1946 */
    -733946400L, /* Sun Sep 29 06:00:00 UTC 1946 */
    -715798800L, /* Sun Apr 27 07:00:00 UTC 1947 */
    -702496800L, /* Sun Sep 28 06:00:00 UTC 1947 */
    -684349200L, /* Sun Apr 25 07:00:00 UTC 1948 */
    -671047200L, /* Sun Sep 26 06:00:00 UTC 1948 */
    -652899600L, /* Sun Apr 24 07:00:00 UTC 1949 */
    -639597600L, /* Sun Sep 25 06:00:00 UTC 1949 */
    -620845200L, /* Sun Apr 30 07:00:00 UTC 1950 */
    -608148000L, /* Sun Sep 24 06:00:00 UTC 1950 */
    -589395600L, /* Sun Apr 29 07:00:00 UTC 1951 */
    -576093600L, /* Sun Sep 30 06:00:00 UTC 1951 */
    -557946000L, /* Sun Apr 27 07:00:00 UTC 1952 */
    -544644000L, /* Sun Sep 28 06:00:00 UTC 1952 */
    -526496400L, /* Sun Apr 26 07:00:00 UTC 1953 */
    -513194400L, /* Sun Sep 27 06:00:00 UTC 1953 */
    -495046800L, /* Sun Apr 25 07:00:00 UTC 1954 */
    -481744800L, /* Sun Sep 26 06:00:00 UTC 1954 */
    -463597200L, /* Sun Apr 24 07:00:00 UTC 1955 */
    -447271200L, /* Sun Oct 30 06:00:00 UTC 1955 */
    -431542800L, /* Sun Apr 29 07:00:00 UTC 1956 */
    -415821600L, /* Sun Oct 28 06:00:00 UTC 1956 */
    -400093200L, /* Sun Apr 28 07:00:00 UTC 1957 */
    -384372000L, /* Sun Oct 27 06:00:00 UTC 1957 */
    -368643600L, /* Sun Apr 27 07:00:00 UTC 1958 */
    -352922400L, /* Sun Oct 26 06:00:00 UTC 1958 */
    -337194000L, /* Sun Apr 26 07:00:00 UTC 1959 */
    -321472800L, /* Sun Oct 25 06:00:00 UTC 1959 */
    -305744400L, /* Sun Apr 24 07:00:00 UTC 1960 */
    -289418400L, /* Sun Oct 30 06:00:00 UTC 1960 */
    -273690000L, /* Sun Apr 30 07:00:00 UTC 1961 */
    -257968800L, /* Sun Oct 29 06:00:00 UTC 1961 */
    -242240400L, /* Sun Apr 29 07:00:00 UTC 1962 */
    -226519200L, /* Sun Oct 28 06:00:00 UTC 1962 */
    -210790800L, /* Sun Apr 28 07:00:00 UTC 1963 */
    -195069600L, /* Sun Oct 27 06:00:00 UTC 1963 */
    -179341200L, /* Sun Apr 26 07:00:00 UTC 1964 */
    -163620000L, /* Sun Oct 25 06:00:00 UTC 1964 */
    -147891600L, /* Sun Apr 25 07:00:00 UTC 1965 */
    -131565600L, /* Sun Oct 31 06:00:00 UTC 1965 */
    -116442000L, /* Sun Apr 24 07:00:00 UTC 1966 */
    -100116000L, /* Sun Oct 30 06:00:00 UTC 1966 */
    -84387600L, /* Sun Apr 30 07:00:00 UTC 1967 */
    -68666400L, /* Sun Oct 29 06:00:00 UTC 1967 */
    -52938000L, /* Sun Apr 28 07:00:00 UTC 1968 */
    -37216800L, /* Sun Oct 27 06:00:00 UTC 1968 */
    -21488400L, /* Sun Apr 27 07:00:00 UTC 1969 */
    -5767200L, /* Sun Oct 26 06:00:00 UTC 1969 */
    9961200L, /* Sun Apr 26 07:00:00 UTC 1970 */
    25682400L, /* Sun Oct 25 06:00:00 UTC 1970 */
    41410800L, /* Sun Apr 25 07:00:00 UTC 1971 */
    57736800L, /* Sun Oct 31 06:00:00 UTC 1971 */
    73465200L, /* Sun Apr 30 07:00:00 UTC 1972 */
    89186400L, /* Sun Oct 29 06:00:00 UTC 1972 */
    104914800L, /* Sun Apr 29 07:00:00 UTC 1973 */
    120636000L, /* Sun Oct 28 06:00:00 UTC 1973 */
    126687600L, /* Sun Jan  6 07:00:00 UTC 1974 */
    152085600L, /* Sun Oct 27 06:00:00 UTC 1974 */
    162370800L, /* Sun Feb 23 07:00:00 UTC 1975 */
    183535200L, /* Sun Oct 26 06:00:00 UTC 1975 */
    199263600L, /* Sun Apr 25 07:00:00 UTC 1976 */
    215589600L, /* Sun Oct 31 06:00:00 UTC 1976 */
    230713200L, /* Sun Apr 24 07:00:00 UTC 1977 */
    247039200L, /* Sun Oct 30 06:00:00 UTC 1977 */
    262767600L, /* Sun Apr 30 07:00:00 UTC 1978 */
    278488800L, /* Sun Oct 29 06:00:00 UTC 1978 */
    294217200L, /* Sun Apr 29 07:00:00 UTC 1979 */
    309938400L, /* Sun Oct 28 06:00:00 UTC 1979 */
    325666800L, /* Sun Apr 27 07:00:00 UTC 1980 */
    341388000L, /* Sun Oct 26 06:00:00 UTC 1980 */
    357116400L, /* Sun Apr 26 07:00:00 UTC 1981 */
    372837600L, /* Sun Oct 25 06:00:00 UTC 1981 */
    388566000L, /* Sun Apr 25 07:00:00 UTC 1982 */
    404892000L, /* Sun Oct 31 06:00:00 UTC 1982 */
    420015600L, /* Sun Apr 24 07:00:00 UTC 1983 */
    436341600L, /* Sun Oct 30 06:00:00 UTC 1983 */
    452070000L, /* Sun Apr 29 07:00:00 UTC 1984 */
    467791200L, /* Sun Oct 28 06:00:00 UTC 1984 */
    483519600L, /* Sun Apr 28 07:00:00 UTC 1985 */
    499240800L, /* Sun Oct 27 06:00:00 UTC 1985 */
    514969200L, /* Sun Apr 27 07:00:00 UTC 1986 */
    530690400L, /* Sun Oct 26 06:00:00 UTC 1986 */
    544604400L, /* Sun Apr  5 07:00:00 UTC 1987 */
    562140000L, /* Sun Oct 25 06:00:00 UTC 1987 */
    576054000L, /* Sun Apr  3 07:00:00 UTC 1988 */
    594194400L, /* Sun Oct 30 06:00:00 UTC 1988 */
    607503600L, /* Sun Apr  2 07:00:00 UTC 1989 */
    625644000L, /* Sun Oct 29 06:00:00 UTC 1989 */
    638953200L, /* Sun Apr  1 07:00:00 UTC 1990 */
    657093600L, /* Sun Oct 28 06:00:00 UTC 1990 */
    671007600L, /* Sun Apr  7 07:00:00 UTC 1991 */
    688543200L, /* Sun Oct 27 06:00:00 UTC 1991 */
    702457200L, /* Sun Apr  5 07:00:00 UTC 1992 */
    719992800L, /* Sun Oct 25 06:00:00 UTC 1992 */
    733906800L, /* Sun Apr  4 07:00:00 UTC 1993 */
    752047200L, /* Sun Oct 31 06:00:00 UTC 1993 */
    765356400L, /* Sun Apr  3 07:00:00 UTC 1994 */
    783496800L, /* Sun Oct 30 06:00:00 UTC 1994 */
    796806000L, /* Sun Apr  2 07:00:00 UTC 1995 */
    814946400L, /* Sun Oct 29 06:00:00 UTC 1995 */
    828860400L, /* Sun Apr  7 07:00:00 UTC 1996 */
    846396000L, /* Sun Oct 27 06:00:00 UTC 1996 */
    860310000L, /* Sun Apr  6 07:00:00 UTC 1997 */
    877845600L, /* Sun Oct 26 06:00:00 UTC 1997 */
    891759600L, /* Sun Apr  5 07:00:00 UTC 1998 */
    909295200L, /* Sun Oct 25 06:00:00 UTC 1998 */
    923209200L, /* Sun Apr  4 07:00:00 UTC 1999 */
    941349600L, /* Sun Oct 31 06:00:00 UTC 1999 */
    954658800L, /* Sun Apr  2 07:00:00 UTC 2000 */
    972799200L, /* Sun Oct 29 06:00:00 UTC 2000 */
    986108400L, /* Sun Apr  1 07:00:00 UTC 2001 */
    1004248800L, /* Sun Oct 28 06:00:00 UTC 2001 */
    1018162800L, /* Sun Apr  7 07:00:00 UTC 2002 */
    1035698400L, /* Sun Oct 27 06:00:00 UTC 2002 */
    1049612400L, /* Sun Apr  6 07:00:00 UTC 2003 */
    1067148000L, /* Sun Oct 26 06:00:00 UTC 2003 */
    1081062000L, /* Sun Apr  4 07:00:00 UTC 2004 */
    1099202400L, /* Sun Oct 31 06:00:00 UTC 2004 */
    1112511600L, /* Sun Apr  3 07:00:00 UTC 2005 */
    1130652000L, /* Sun Oct 30 06:00:00 UTC 2005 */
    1143961200L, /* Sun Apr  2 07:00:00 UTC 2006 */
    1162101600L, /* Sun Oct 29 06:00:00 UTC 2006 */
    1173596400L, /* Sun Mar 11 07:00:00 UTC 2007 */
    1194156000L, /* Sun Nov  4 06:00:00 UTC 2007 */
    1205046000L, /* Sun Mar  9 07:00:00 UTC 2008 */
    1225605600L, /* Sun Nov  2 06:00:00 UTC 2008 */
    1236495600L, /* Sun Mar  8 07:00:00 UTC 2009 */
    1257055200L, /* Sun Nov  1 06:00:00 UTC 2009 */
    1268550000L, /* Sun Mar 14 07:00:00 UTC 2010 */
    1289109600L, /* Sun Nov  7 06:00:00 UTC 2010 */
    1299999600L, /* Sun Mar 13 07:00:00 UTC 2011 */
    1320559200L, /* Sun Nov  6 06:00:00 UTC 2011 */
    1331449200L, /* Sun Mar 11 07:00:00 UTC 2012 */
    1352008800L, /* Sun Nov  4 06:00:00 UTC 2012 */
    1362898800L, /* Sun Mar 10 07:00:00 UTC 2013 */
    1383458400L, /* Sun Nov  3 06:00:00 UTC 2013 */
    1394348400L, /* Sun Mar  9 07:00:00 UTC 2014 */
    1414908000L, /* Sun Nov  2 06:00:00 UTC 2014 */
    1425798000L, /* Sun Mar  8 07:00:00 UTC 2015 */
    1446357600L, /* Sun Nov  1 06:00:00 UTC 2015 */
    1457852400L, /* Sun Mar 13 07:00:00 UTC 2016 */
    1478412000L, /* Sun Nov  6 06:00:00 UTC 2016 */
    1489302000L, /* Sun Mar 12 07:00:00 UTC 2017 */
    1509861600L, /* Sun Nov  5 06:00:00 UTC 2017 */
    1520751600L, /* Sun Mar 11 07:00:00 UTC 2018 */
    1541311200L, /* Sun Nov  4 06:00:00 UTC 2018 */
    1552201200L, /* Sun Mar 10 07:00:00 UTC 2019 */
    1572760800L, /* Sun Nov  3 06:00:00 UTC 2019 */
    1583650800L, /* Sun Mar  8 07:00:00 UTC 2020 */
    1604210400L, /* Sun Nov  1 06:00:00 UTC 2020 */
    1615705200L, /* Sun Mar 14 07:00:00 UTC 2021 */
    1636264800L, /* Sun Nov  7 06:00:00 UTC 2021 */
    1647154800L, /* Sun Mar 13 07:00:00 UTC 2022 */
    1667714400L, /* Sun Nov  6 06:00:00 UTC 2022 */
    1678604400L, /* Sun Mar 12 07:00:00 UTC 2023 */
    1699164000L, /* Sun Nov  5 06:00:00 UTC 2023 */
    1710054000L, /* Sun Mar 10 07:00:00 UTC 2024 */
    1730613600L, /* Sun Nov  3 06:00:00 UTC 2024 */
    1741503600L, /* Sun Mar  9 07:00:00 UTC 2025 */
    1762063200L, /* Sun Nov  2 06:00:00 UTC 2025 */
    1772953200L, /* Sun Mar  8 07:00:00 UTC 2026 */
    1793512800L, /* Sun Nov  1 06:00:00 UTC 2026 */
    1805007600L, /* Sun Mar 14 07:00:00 UTC 2027 */
    1825567200L, /* Sun Nov  7 06:00:00 UTC 2027 */
    1836457200L, /* Sun Mar 12 07:00:00 UTC 2028 */
    1857016800L, /* Sun Nov  5 06:00:00 UTC 2028 */
    1867906800L, /* Sun Mar 11 07:00:00 UTC 2029 */
    1888466400L, /* Sun Nov  4 06:00:00 UTC 2029 */
    1899356400L, /* Sun Mar 10 07:00:00 UTC 2030 */
    1919916000L, /* Sun Nov  3 06:00:00 UTC 2030 */
    1930806000L, /* Sun Mar  9 07:00:00 UTC 2031 */
    1951365600L, /* Sun Nov  2 06:00:00 UTC 2031 */
    1962860400L, /* Sun Mar 14 07:00:00 UTC 2032 */
    1983420000L, /* Sun Nov  7 06:00:00 UTC 2032 */
    1994310000L, /* Sun Mar 13 07:00:00 UTC 2033 */
    2014869600L, /* Sun Nov  6 06:00:00 UTC 2033 */
    2025759600L, /* Sun Mar 12 07:00:00 UTC 2034 */
    2046319200L, /* Sun Nov  5 06:00:00 UTC 2034 */
    2057209200L, /* Sun Mar 11 07:00:00 UTC 2035 */
    2077768800L, /* Sun Nov  4 06:00:00 UTC 2035 */
    2088658800L, /* Sun Mar  9 07:00:00 UTC 2036 */
    2109218400L, /* Sun Nov  2 06:00:00 UTC 2036 */
    2120108400L, /* Sun Mar  8 07:00:00 UTC 2037 */
    2140668000L, /* Sun Nov  1 06:00:00 UTC 2037 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L  /* Thu Jan  1 00:00:00 UTC 1970 */
#if TZ_MAX_TIMES > 320
    ,
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L, /* Thu Jan  1 00:00:00 UTC 1970 */
    0L  /* Thu Jan  1 00:00:00 UTC 1970 */
#endif
  },
  {  /* types */
    3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
    2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
    2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
    2, 4, 5, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,
    1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
#if TZ_MAX_TIMES > 320
    ,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
#endif
  },
  {  /* ttis */
    { -17762, 0, 0, 0, 0 }, { -14400, 4, 1, 0, 0 },
    { -18000, 8, 0, 0, 0 }, { -18000, 8, 0, 1, 1 },
    { -14400, 12, 1, 0, 0 }, { -14400, 16, 1, 1, 1 },
    { -18000, 8, 0, 0, 0 }, { -14400, 4, 1, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }
#if TZ_MAX_TYPES > 20
    ,
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }
#endif
  },
  {  /* chars */
    'L', 'M', 'T', '\0',
    'E', 'D', 'T', '\0',
    'E', 'S', 'T', '\0',
    'E', 'W', 'T', '\0',
    'E', 'P', 'T', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0',
    '\0', '\0'
  },
  {  /* lsis */
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }
  }
};
