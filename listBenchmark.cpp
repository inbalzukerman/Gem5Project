#include "m5op.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

extern "C"{
void map_m5_mem();
}

struct node {
	int data;
	struct node * next;
};

typedef struct node Node;

// created with listGenerator.py
int initial_size = 100 ;
Node initial [ 100 ] = {
	{.data = -1 }, {.data = 9 }, {.data = 10 }, {.data = 14 }, {.data = 25 }, {.data = 30 }, {.data = 44 }, {.data = 45 }, {.data = 52 }, {.data = 69 }, {.data = 70 }, {.data = 72 }, {.data = 78 }, {.data = 88 }, {.data = 89 }, {.data = 105 }, {.data = 116 }, {.data = 122 }, {.data = 140 }, {.data = 143 }, {.data = 151 }, {.data = 169 }, {.data = 188 }, {.data = 191 }, {.data = 196 }, {.data = 201 }, {.data = 225 }, {.data = 250 }, {.data = 259 }, {.data = 267 }, {.data = 272 }, {.data = 285 }, {.data = 291 }, {.data = 298 }, {.data = 307 }, {.data = 312 }, {.data = 340 }, {.data = 351 }, {.data = 371 }, {.data = 381 }, {.data = 402 }, {.data = 408 }, {.data = 415 }, {.data = 436 }, {.data = 439 }, {.data = 448 }, {.data = 458 }, {.data = 468 }, {.data = 470 }, {.data = 487 }, {.data = 504 }, {.data = 511 }, {.data = 521 }, {.data = 533 }, {.data = 546 }, {.data = 556 }, {.data = 558 }, {.data = 562 }, {.data = 571 }, {.data = 575 }, {.data = 593 }, {.data = 595 }, {.data = 606 }, {.data = 615 }, {.data = 620 }, {.data = 629 }, {.data = 630 }, {.data = 636 }, {.data = 643 }, {.data = 698 }, {.data = 703 }, {.data = 715 }, {.data = 718 }, {.data = 755 }, {.data = 758 }, {.data = 769 }, {.data = 773 }, {.data = 791 }, {.data = 805 }, {.data = 823 }, {.data = 838 }, {.data = 848 }, {.data = 850 }, {.data = 851 }, {.data = 864 }, {.data = 868 }, {.data = 874 }, {.data = 883 }, {.data = 884 }, {.data = 907 }, {.data = 927 }, {.data = 940 }, {.data = 942 }, {.data = 951 }, {.data = 957 }, {.data = 964 }, {.data = 973 }, {.data = 981 }, {.data = 993 }, {.data = 1001 }, 
};

int nodes_size = 902 ;
Node nodes [ 902 ] = {
	{.data = 316 }, {.data = 641 }, {.data = 204 }, {.data = 853 }, {.data = 222 }, {.data = 391 }, {.data = 686 }, {.data = 623 }, {.data = 472 }, {.data = 389 }, {.data = 388 }, {.data = 147 }, {.data = 892 }, {.data = 876 }, {.data = 359 }, {.data = 982 }, {.data = 893 }, {.data = 186 }, {.data = 806 }, {.data = 649 }, {.data = 281 }, {.data = 875 }, {.data = 422 }, {.data = 124 }, {.data = 161 }, {.data = 662 }, {.data = 485 }, {.data = 631 }, {.data = 820 }, {.data = 582 }, {.data = 783 }, {.data = 928 }, {.data = 920 }, {.data = 317 }, {.data = 674 }, {.data = 166 }, {.data = 725 }, {.data = 369 }, {.data = 103 }, {.data = 361 }, {.data = 8 }, {.data = 118 }, {.data = 248 }, {.data = 650 }, {.data = 58 }, {.data = 905 }, {.data = 994 }, {.data = 979 }, {.data = 319 }, {.data = 670 }, {.data = 227 }, {.data = 922 }, {.data = 40 }, {.data = 668 }, {.data = 731 }, {.data = 261 }, {.data = 617 }, {.data = 588 }, {.data = 733 }, {.data = 65 }, {.data = 935 }, {.data = 858 }, {.data = 162 }, {.data = 134 }, {.data = 541 }, {.data = 557 }, {.data = 21 }, {.data = 821 }, {.data = 179 }, {.data = 424 }, {.data = 528 }, {.data = 777 }, {.data = 727 }, {.data = 962 }, {.data = 145 }, {.data = 370 }, {.data = 811 }, {.data = 128 }, {.data = 953 }, {.data = 779 }, {.data = 273 }, {.data = 228 }, {.data = 125 }, {.data = 543 }, {.data = 329 }, {.data = 231 }, {.data = 785 }, {.data = 747 }, {.data = 873 }, {.data = 226 }, {.data = 566 }, {.data = 268 }, {.data = 28 }, {.data = 944 }, {.data = 327 }, {.data = 978 }, {.data = 181 }, {.data = 917 }, {.data = 238 }, {.data = 385 }, {.data = 833 }, {.data = 275 }, {.data = 925 }, {.data = 855 }, {.data = 224 }, {.data = 491 }, {.data = 891 }, {.data = 954 }, {.data = 305 }, {.data = 83 }, {.data = 87 }, {.data = 740 }, {.data = 640 }, {.data = 97 }, {.data = 253 }, {.data = 550 }, {.data = 741 }, {.data = 720 }, {.data = 937 }, {.data = 286 }, {.data = 618 }, {.data = 508 }, {.data = 257 }, {.data = 67 }, {.data = 91 }, {.data = 184 }, {.data = 687 }, {.data = 540 }, {.data = 397 }, {.data = 866 }, {.data = 255 }, {.data = 4 }, {.data = 107 }, {.data = 770 }, {.data = 941 }, {.data = 386 }, {.data = 461 }, {.data = 803 }, {.data = 564 }, {.data = 988 }, {.data = 887 }, {.data = 74 }, {.data = 302 }, {.data = 126 }, {.data = 956 }, {.data = 739 }, {.data = 208 }, {.data = 5 }, {.data = 830 }, {.data = 393 }, {.data = 923 }, {.data = 360 }, {.data = 878 }, {.data = 336 }, {.data = 37 }, {.data = 35 }, {.data = 737 }, {.data = 673 }, {.data = 624 }, {.data = 555 }, {.data = 816 }, {.data = 221 }, {.data = 914 }, {.data = 807 }, {.data = 736 }, {.data = 761 }, {.data = 149 }, {.data = 101 }, {.data = 841 }, {.data = 50 }, {.data = 112 }, {.data = 843 }, {.data = 778 }, {.data = 47 }, {.data = 155 }, {.data = 365 }, {.data = 170 }, {.data = 357 }, {.data = 49 }, {.data = 952 }, {.data = 430 }, {.data = 525 }, {.data = 756 }, {.data = 350 }, {.data = 26 }, {.data = 711 }, {.data = 36 }, {.data = 661 }, {.data = 570 }, {.data = 705 }, {.data = 839 }, {.data = 345 }, {.data = 613 }, {.data = 822 }, {.data = 43 }, {.data = 168 }, {.data = 486 }, {.data = 313 }, {.data = 924 }, {.data = 229 }, {.data = 82 }, {.data = 669 }, {.data = 378 }, {.data = 888 }, {.data = 972 }, {.data = 573 }, {.data = 677 }, {.data = 717 }, {.data = 314 }, {.data = 6 }, {.data = 531 }, {.data = 11 }, {.data = 220 }, {.data = 591 }, {.data = 374 }, {.data = 243 }, {.data = 896 }, {.data = 658 }, {.data = 384 }, {.data = 210 }, {.data = 499 }, {.data = 997 }, {.data = 998 }, {.data = 911 }, {.data = 211 }, {.data = 480 }, {.data = 782 }, {.data = 812 }, {.data = 320 }, {.data = 702 }, {.data = 367 }, {.data = 932 }, {.data = 258 }, {.data = 561 }, {.data = 786 }, {.data = 326 }, {.data = 76 }, {.data = 939 }, {.data = 688 }, {.data = 347 }, {.data = 331 }, {.data = 176 }, {.data = 249 }, {.data = 694 }, {.data = 867 }, {.data = 817 }, {.data = 29 }, {.data = 590 }, {.data = 789 }, {.data = 137 }, {.data = 94 }, {.data = 701 }, {.data = 251 }, {.data = 276 }, {.data = 722 }, {.data = 680 }, {.data = 57 }, {.data = 173 }, {.data = 872 }, {.data = 913 }, {.data = 846 }, {.data = 592 }, {.data = 269 }, {.data = 598 }, {.data = 774 }, {.data = 692 }, {.data = 708 }, {.data = 578 }, {.data = 645 }, {.data = 517 }, {.data = 154 }, {.data = 404 }, {.data = 465 }, {.data = 346 }, {.data = 445 }, {.data = 62 }, {.data = 861 }, {.data = 967 }, {.data = 177 }, {.data = 435 }, {.data = 585 }, {.data = 644 }, {.data = 781 }, {.data = 401 }, {.data = 93 }, {.data = 31 }, {.data = 860 }, {.data = 454 }, {.data = 342 }, {.data = 413 }, {.data = 810 }, {.data = 910 }, {.data = 934 }, {.data = 442 }, {.data = 46 }, {.data = 71 }, {.data = 619 }, {.data = 594 }, {.data = 419 }, {.data = 659 }, {.data = 503 }, {.data = 646 }, {.data = 428 }, {.data = 763 }, {.data = 790 }, {.data = 476 }, {.data = 946 }, {.data = 713 }, {.data = 328 }, {.data = 579 }, {.data = 453 }, {.data = 282 }, {.data = 152 }, {.data = 142 }, {.data = 300 }, {.data = 165 }, {.data = 955 }, {.data = 616 }, {.data = 104 }, {.data = 647 }, {.data = 970 }, {.data = 826 }, {.data = 831 }, {.data = 236 }, {.data = 354 }, {.data = 284 }, {.data = 297 }, {.data = 339 }, {.data = 516 }, {.data = 574 }, {.data = 349 }, {.data = 194 }, {.data = 551 }, {.data = 84 }, {.data = 364 }, {.data = 510 }, {.data = 728 }, {.data = 497 }, {.data = 423 }, {.data = 493 }, {.data = 634 }, {.data = 429 }, {.data = 895 }, {.data = 547 }, {.data = 139 }, {.data = 290 }, {.data = 986 }, {.data = 373 }, {.data = 209 }, {.data = 441 }, {.data = 852 }, {.data = 450 }, {.data = 877 }, {.data = 577 }, {.data = 432 }, {.data = 603 }, {.data = 545 }, {.data = 212 }, {.data = 399 }, {.data = 193 }, {.data = 271 }, {.data = 245 }, {.data = 898 }, {.data = 612 }, {.data = 296 }, {.data = 842 }, {.data = 198 }, {.data = 233 }, {.data = 333 }, {.data = 23 }, {.data = 60 }, {.data = 933 }, {.data = 324 }, {.data = 776 }, {.data = 948 }, {.data = 38 }, {.data = 642 }, {.data = 639 }, {.data = 277 }, {.data = 975 }, {.data = 203 }, {.data = 602 }, {.data = 153 }, {.data = 13 }, {.data = 167 }, {.data = 507 }, {.data = 745 }, {.data = 608 }, {.data = 159 }, {.data = 279 }, {.data = 235 }, {.data = 729 }, {.data = 395 }, {.data = 237 }, {.data = 379 }, {.data = 824 }, {.data = 554 }, {.data = 32 }, {.data = 622 }, {.data = 568 }, {.data = 96 }, {.data = 506 }, {.data = 657 }, {.data = 252 }, {.data = 775 }, {.data = 880 }, {.data = 295 }, {.data = 813 }, {.data = 992 }, {.data = 572 }, {.data = 751 }, {.data = 664 }, {.data = 835 }, {.data = 621 }, {.data = 707 }, {.data = 886 }, {.data = 601 }, {.data = 148 }, {.data = 478 }, {.data = 738 }, {.data = 794 }, {.data = 418 }, {.data = 780 }, {.data = 532 }, {.data = 753 }, {.data = 81 }, {.data = 66 }, {.data = 216 }, {.data = 410 }, {.data = 466 }, {.data = 132 }, {.data = 138 }, {.data = 996 }, {.data = 157 }, {.data = 421 }, {.data = 323 }, {.data = 560 }, {.data = 182 }, {.data = 98 }, {.data = 310 }, {.data = 534 }, {.data = 111 }, {.data = 765 }, {.data = 455 }, {.data = 311 }, {.data = 178 }, {.data = 535 }, {.data = 56 }, {.data = 232 }, {.data = 80 }, {.data = 239 }, {.data = 655 }, {.data = 477 }, {.data = 474 }, {.data = 983 }, {.data = 451 }, {.data = 407 }, {.data = 633 }, {.data = 614 }, {.data = 427 }, {.data = 684 }, {.data = 400 }, {.data = 68 }, {.data = 999 }, {.data = 901 }, {.data = 632 }, {.data = 869 }, {.data = 337 }, {.data = 409 }, {.data = 734 }, {.data = 512 }, {.data = 190 }, {.data = 637 }, {.data = 689 }, {.data = 524 }, {.data = 931 }, {.data = 368 }, {.data = 768 }, {.data = 704 }, {.data = 457 }, {.data = 200 }, {.data = 55 }, {.data = 202 }, {.data = 549 }, {.data = 706 }, {.data = 628 }, {.data = 666 }, {.data = 671 }, {.data = 518 }, {.data = 344 }, {.data = 434 }, {.data = 321 }, {.data = 605 }, {.data = 332 }, {.data = 473 }, {.data = 283 }, {.data = 596 }, {.data = 495 }, {.data = 672 }, {.data = 797 }, {.data = 552 }, {.data = 890 }, {.data = 987 }, {.data = 498 }, {.data = 829 }, {.data = 906 }, {.data = 3 }, {.data = 207 }, {.data = 270 }, {.data = 120 }, {.data = 230 }, {.data = 787 }, {.data = 123 }, {.data = 417 }, {.data = 163 }, {.data = 102 }, {.data = 828 }, {.data = 635 }, {.data = 492 }, {.data = 433 }, {.data = 903 }, {.data = 509 }, {.data = 991 }, {.data = 971 }, {.data = 456 }, {.data = 420 }, {.data = 685 }, {.data = 99 }, {.data = 348 }, {.data = 750 }, {.data = 244 }, {.data = 697 }, {.data = 187 }, {.data = 648 }, {.data = 471 }, {.data = 968 }, {.data = 514 }, {.data = 335 }, {.data = 115 }, {.data = 482 }, {.data = 79 }, {.data = 959 }, {.data = 278 }, {.data = 494 }, {.data = 969 }, {.data = 609 }, {.data = 752 }, {.data = 870 }, {.data = 834 }, {.data = 469 }, {.data = 160 }, {.data = 90 }, {.data = 376 }, {.data = 693 }, {.data = 41 }, {.data = 576 }, {.data = 92 }, {.data = 464 }, {.data = 542 }, {.data = 304 }, {.data = 240 }, {.data = 719 }, {.data = 199 }, {.data = 691 }, {.data = 288 }, {.data = 990 }, {.data = 185 }, {.data = 241 }, {.data = 762 }, {.data = 958 }, {.data = 218 }, {.data = 977 }, {.data = 488 }, {.data = 881 }, {.data = 963 }, {.data = 34 }, {.data = 109 }, {.data = 59 }, {.data = 882 }, {.data = 265 }, {.data = 679 }, {.data = 879 }, {.data = 771 }, {.data = 334 }, {.data = 500 }, {.data = 653 }, {.data = 915 }, {.data = 341 }, {.data = 597 }, {.data = 438 }, {.data = 716 }, {.data = 844 }, {.data = 897 }, {.data = 343 }, {.data = 121 }, {.data = 859 }, {.data = 936 }, {.data = 743 }, {.data = 894 }, {.data = 663 }, {.data = 565 }, {.data = 214 }, {.data = 974 }, {.data = 363 }, {.data = 356 }, {.data = 1 }, {.data = 587 }, {.data = 406 }, {.data = 900 }, {.data = 17 }, {.data = 742 }, {.data = 520 }, {.data = 172 }, {.data = 690 }, {.data = 730 }, {.data = 390 }, {.data = 862 }, {.data = 569 }, {.data = 460 }, {.data = 414 }, {.data = 411 }, {.data = 174 }, {.data = 362 }, {.data = 586 }, {.data = 818 }, {.data = 260 }, {.data = 889 }, {.data = 135 }, {.data = 801 }, {.data = 484 }, {.data = 660 }, {.data = 489 }, {.data = 352 }, {.data = 42 }, {.data = 459 }, {.data = 912 }, {.data = 405 }, {.data = 15 }, {.data = 984 }, {.data = 303 }, {.data = 675 }, {.data = 735 }, {.data = 827 }, {.data = 119 }, {.data = 919 }, {.data = 502 }, {.data = 293 }, {.data = 760 }, {.data = 809 }, {.data = 64 }, {.data = 437 }, {.data = 584 }, {.data = 77 }, {.data = 501 }, {.data = 301 }, {.data = 219 }, {.data = 213 }, {.data = 449 }, {.data = 426 }, {.data = 665 }, {.data = 625 }, {.data = 133 }, {.data = 95 }, {.data = 117 }, {.data = 754 }, {.data = 18 }, {.data = 699 }, {.data = 683 }, {.data = 490 }, {.data = 539 }, {.data = 175 }, {.data = 61 }, {.data = 515 }, {.data = 712 }, {.data = 724 }, {.data = 308 }, {.data = 180 }, {.data = 949 }, {.data = 536 }, {.data = 652 }, {.data = 804 }, {.data = 819 }, {.data = 496 }, {.data = 857 }, {.data = 709 }, {.data = 246 }, {.data = 22 }, {.data = 945 }, {.data = 452 }, {.data = 0 }, {.data = 808 }, {.data = 294 }, {.data = 195 }, {.data = 746 }, {.data = 732 }, {.data = 215 }, {.data = 7 }, {.data = 681 }, {.data = 899 }, {.data = 234 }, {.data = 141 }, {.data = 431 }, {.data = 100 }, {.data = 563 }, {.data = 798 }, {.data = 519 }, {.data = 856 }, {.data = 526 }, {.data = 726 }, {.data = 19 }, {.data = 2 }, {.data = 759 }, {.data = 479 }, {.data = 559 }, {.data = 849 }, {.data = 710 }, {.data = 129 }, {.data = 538 }, {.data = 714 }, {.data = 902 }, {.data = 796 }, {.data = 372 }, {.data = 256 }, {.data = 315 }, {.data = 656 }, {.data = 242 }, {.data = 916 }, {.data = 904 }, {.data = 599 }, {.data = 795 }, {.data = 748 }, {.data = 847 }, {.data = 947 }, {.data = 39 }, {.data = 338 }, {.data = 885 }, {.data = 788 }, {.data = 676 }, {.data = 54 }, {.data = 654 }, {.data = 394 }, {.data = 836 }, {.data = 832 }, {.data = 757 }, {.data = 695 }, {.data = 840 }, {.data = 63 }, {.data = 292 }, {.data = 16 }, {.data = 377 }, {.data = 976 }, {.data = 721 }, {.data = 799 }, {.data = 908 }, {.data = 48 }, {.data = 854 }, {.data = 980 }, {.data = 667 }, {.data = 581 }, {.data = 387 }, {.data = 403 }, {.data = 909 }, {.data = 358 }, {.data = 523 }, {.data = 627 }, {.data = 131 }, {.data = 110 }, {.data = 462 }, {.data = 611 }, {.data = 287 }, {.data = 553 }, {.data = 700 }, {.data = 522 }, {.data = 800 }, {.data = 929 }, {.data = 583 }, {.data = 682 }, {.data = 280 }, {.data = 254 }, {.data = 158 }, {.data = 355 }, {.data = 651 }, {.data = 918 }, {.data = 845 }, {.data = 837 }, {.data = 223 }, {.data = 529 }, {.data = 309 }, {.data = 960 }, {.data = 206 }, {.data = 263 }, {.data = 247 }, {.data = 85 }, {.data = 938 }, {.data = 396 }, {.data = 12 }, {.data = 86 }, {.data = 444 }, {.data = 412 }, {.data = 189 }, {.data = 995 }, {.data = 481 }, {.data = 366 }, {.data = 764 }, {.data = 814 }, {.data = 20 }, {.data = 425 }, {.data = 961 }, {.data = 53 }, {.data = 638 }, {.data = 75 }, {.data = 600 }, {.data = 183 }, {.data = 467 }, {.data = 443 }, {.data = 113 }, {.data = 483 }, {.data = 144 }, {.data = 114 }, {.data = 108 }, {.data = 322 }, {.data = 289 }, {.data = 475 }, {.data = 678 }, {.data = 548 }, {.data = 51 }, {.data = 446 }, {.data = 505 }, {.data = 440 }, {.data = 792 }, {.data = 766 }, {.data = 825 }, {.data = 197 }, {.data = 24 }, {.data = 416 }, {.data = 318 }, {.data = 136 }, {.data = 965 }, {.data = 696 }, {.data = 530 }, {.data = 926 }, {.data = 146 }, {.data = 943 }, {.data = 330 }, {.data = 966 }, {.data = 375 }, {.data = 871 }, {.data = 607 }, {.data = 306 }, {.data = 513 }, {.data = 164 }, {.data = 580 }, {.data = 33 }, {.data = 537 }, {.data = 793 }, {.data = 299 }, {.data = 447 }, {.data = 130 }, {.data = 863 }, {.data = 398 }, {.data = 744 }, {.data = 150 }, {.data = 382 }, {.data = 262 }, {.data = 383 }, {.data = 784 }, {.data = 156 }, {.data = 325 }, {.data = 171 }, {.data = 205 }, {.data = 217 }, {.data = 567 }, {.data = 380 }, {.data = 989 }, {.data = 815 }, {.data = 767 }, {.data = 802 }, {.data = 73 }, {.data = 463 }, {.data = 930 }, {.data = 544 }, {.data = 723 }, {.data = 604 }, {.data = 749 }, {.data = 527 }, {.data = 266 }, {.data = 772 }, {.data = 127 }, {.data = 353 }, {.data = 192 }, {.data = 106 }, {.data = 865 }, {.data = 950 }, {.data = 985 }, {.data = 921 }, {.data = 589 }, {.data = 274 }, {.data = 610 }, {.data = 264 }, {.data = 626 }, {.data = 392 }, {.data = 27 }, 
};

int max = initial_size+nodes_size;

//returns the data after which newNode was added
int insert(Node& begin, Node& newNode){
	if(begin.data > newNode.data){
		//shouldn't happen!
		newNode.next=&begin;
		return -9999999;
	}
	Node* n;

	for(n=&begin; n->next!= NULL; n=n->next){
		if((n->data <= newNode.data) &&  (newNode.data < n->next->data)){
			newNode.next=n->next;
			n->next = &newNode;
			return n->data;	
		}
	}

	//shouldn't happen
	n->next = &newNode;
	return 999999999999;
}

void printList(Node& begin, string delimiter){
	int i=0;
	cout << "===============================================================" <<endl;
	cout << "the list" << endl;
	for(Node* n=&begin; n!= NULL; n=n->next){
		cout << n->data;
		if(n->next != NULL)
			cout << delimiter;
		if(i>0 && i++%10 == 0)
			cout << endl;
	}
	cout << "\n===============================================================" <<endl;
	cout <<"\n"<< endl;
}

void printList(Node& begin){
	printList(begin, " -> ");
}

void printNodes(int newline){
	cout << "===============================================================" <<endl;
	cout << "nodes in array:" <<endl;
	for(int i=0; i < nodes_size; i++){
		cout << nodes[i].data;
		if(i+1 != max)
			cout << " , ";
		if(i>0 && i%10 == 0)
			cout << endl;
		if(i>0 && i%newline == 0)
			cout << "\n"<<endl;
	}
	cout << "\n===============================================================" <<endl;
	cout <<"\n"<< endl;
}
 
//run as listBenchmark debug for verbose version
int main (int argc, char *argv[]){

	map_m5_mem();

	//initialize list 
	for(int i=0; i < initial_size-1 ; i++)
		initial[i].next = &initial[i+1];

	//initial[initial_size-1].next = NULL;

	Node begin = initial[0];
	Node end = initial[initial_size-1];

	printList(begin);
	
	//Adding the nodes' addresses to our DB in the simulator
	/*for(int i = 0; i<= initial_size-1; i++){
		m5_addsymbol( 42, (char*) &initial[i]);
	}

	for(int i = 0; i<= nodes_size-1; i++){
		m5_addsymbol( 42, (char*) &nodes[i]); 
	}*/

	m5_reset_stats(0,0);

	cout << "Done reset stats" << endl;
	cout << "START LIST BENCHMARK" << endl;

	m5_addsymbol( 43, NULL);
	#pragma omp parallel shared(begin,end,nodes) num_threads(4)
	{

		int tid = omp_get_thread_num();
	    int nthreads = omp_get_num_threads();

	    if(tid ==0){
	    	printf("number of threads is:%d\n", nthreads );
	    }
	    int beginIndex = (nodes_size/nthreads)*tid;
		int endIndex = (tid+1 != nthreads)? (nodes_size/nthreads)*(tid+1) : nodes_size;


		for(int i = beginIndex; i < endIndex; i++){
			int where = insert(begin, nodes[i]);
		}
 
		
	}
	m5_addsymbol( 43, NULL);

	cout << "Done working on the list" << endl;
	m5_dumpreset_stats(0,0);

	cout << "Done dumping stats" << endl;

	cout << "DONE list BENCHMARK" << endl;
	
	//post info print
	printList(begin, ","); 

}