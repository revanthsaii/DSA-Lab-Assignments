#include <stdio.h>
#include <string.h>

#define MAX_DAYS      7
#define MAX_PERIODS   10
#define MAX_SECTIONS  5
#define MAX_SUBJECTS  50
#define MAX_LABS      30

typedef struct {
    int id;
    char name[32];
    int teacherId;
    int sectionId;        /* 0..sections-1 */
    int lecturesPerWeek;
    int hasLab;           /* 1 if has 2-period lab */
} Subject;

typedef struct {
    int subjectId;
    int teacherId;
    int sectionId;
    int sessionsPerWeek;  /* blocks of 2 periods */
} Lab;

typedef struct {
    int subjectId;        /* -1 = FREE */
    int isLabPart;        /* 1 if part of lab block */
} Slot;

/* Configurable parameters */
int DAYS;
int PERIODS;
int SECTIONS;

/* Data */
Subject subjects[MAX_SUBJECTS];
int subjectCount = 0;

Lab labs[MAX_LABS];
int labCount = 0;

/* timetable[section][day][period] */
Slot timetableSlots[MAX_SECTIONS][MAX_DAYS][MAX_PERIODS];

/* teacherAtTime[day * PERIODS + period] = teacherId or -1 */
int teacherAtTime[MAX_DAYS * MAX_PERIODS];

/* sectionBusy[(day * PERIODS + period) * SECTIONS + section] = 1 if occupied */
int sectionBusy[MAX_DAYS * MAX_PERIODS * MAX_SECTIONS];

/* usage counters indexed by subjectId */
int usedLectures[MAX_SUBJECTS];
int usedLabBlocks[MAX_SUBJECTS];

/* section names for printing */
char sectionNames[MAX_SECTIONS][32];

int slotKey(int day, int period, int section) {
    return (day * PERIODS + period) * SECTIONS + section;
}

Subject* getSubjectById(int id) {
    int i;
    for (i = 0; i < subjectCount; ++i) {
        if (subjects[i].id == id) return &subjects[i];
    }
    return NULL;
}

/* ---------- Lecture placement constraints ---------- */

int canPlaceLecture(const Subject *sub, int day, int period, int section) {
    int timeKey = day * PERIODS + period;
    int secKey = slotKey(day, period, section);
    int p;

    if (sub->sectionId != section) return 0;
    if (usedLectures[sub->id] >= sub->lecturesPerWeek) return 0;

    if (teacherAtTime[timeKey] != -1 &&
        teacherAtTime[timeKey] == sub->teacherId)
        return 0;

    if (sectionBusy[secKey]) return 0;

    /* At most one lecture of this subject per day per section */
    for (p = 0; p < PERIODS; ++p) {
        if (timetableSlots[section][day][p].subjectId == sub->id)
            return 0;
    }

    return 1;
}

void placeLecture(const Subject *sub, int day, int period, int section) {
    int timeKey = day * PERIODS + period;
    int secKey = slotKey(day, period, section);

    timetableSlots[section][day][period].subjectId = sub->id;
    timetableSlots[section][day][period].isLabPart = 0;
    teacherAtTime[timeKey] = sub->teacherId;
    sectionBusy[secKey] = 1;
    usedLectures[sub->id]++;
}

void removeLecture(const Subject *sub, int day, int period, int section) {
    int timeKey = day * PERIODS + period;
    int secKey = slotKey(day, period, section);

    timetableSlots[section][day][period].subjectId = -1;
    timetableSlots[section][day][period].isLabPart = 0;
    if (teacherAtTime[timeKey] == sub->teacherId)
        teacherAtTime[timeKey] = -1;
    sectionBusy[secKey] = 0;
    usedLectures[sub->id]--;
}

/* ---------- Lab (2-period block) constraints ---------- */

int canPlaceLabBlock(const Lab *labInfo, int day, int startPeriod, int section) {
    int p1, p2;
    int timeKey1, timeKey2;
    int secKey1, secKey2;
    Subject *sub;
    int p;

    if (labInfo->sectionId != section) return 0;
    if (startPeriod + 1 >= PERIODS) return 0;
    if (usedLabBlocks[labInfo->subjectId] >= labInfo->sessionsPerWeek)
        return 0;

    p1 = startPeriod;
    p2 = startPeriod + 1;

    timeKey1 = day * PERIODS + p1;
    timeKey2 = day * PERIODS + p2;
    secKey1 = slotKey(day, p1, section);
    secKey2 = slotKey(day, p2, section);

    if (teacherAtTime[timeKey1] != -1 &&
        teacherAtTime[timeKey1] == labInfo->teacherId)
        return 0;
    if (teacherAtTime[timeKey2] != -1 &&
        teacherAtTime[timeKey2] == labInfo->teacherId)
        return 0;

    if (sectionBusy[secKey1] || sectionBusy[secKey2])
        return 0;

    if (timetableSlots[section][day][p1].subjectId != -1) return 0;
    if (timetableSlots[section][day][p2].subjectId != -1) return 0;

    sub = getSubjectById(labInfo->subjectId);
    if (sub == NULL) return 0;

    /* Avoid another same subject on that day */
    for (p = 0; p < PERIODS; ++p) {
        if (timetableSlots[section][day][p].subjectId == sub->id)
            return 0;
    }

    return 1;
}

void placeLabBlock(const Lab *labInfo, int day, int startPeriod, int section) {
    int p1 = startPeriod;
    int p2 = startPeriod + 1;
    int timeKey1 = day * PERIODS + p1;
    int timeKey2 = day * PERIODS + p2;
    int secKey1 = slotKey(day, p1, section);
    int secKey2 = slotKey(day, p2, section);

    timetableSlots[section][day][p1].subjectId = labInfo->subjectId;
    timetableSlots[section][day][p2].subjectId = labInfo->subjectId;
    timetableSlots[section][day][p1].isLabPart = 1;
    timetableSlots[section][day][p2].isLabPart = 1;

    teacherAtTime[timeKey1] = labInfo->teacherId;
    teacherAtTime[timeKey2] = labInfo->teacherId;
    sectionBusy[secKey1] = 1;
    sectionBusy[secKey2] = 1;

    usedLabBlocks[labInfo->subjectId]++;
}

void removeLabBlock(const Lab *labInfo, int day, int startPeriod, int section) {
    int p1 = startPeriod;
    int p2 = startPeriod + 1;
    int timeKey1 = day * PERIODS + p1;
    int timeKey2 = day * PERIODS + p2;
    int secKey1 = slotKey(day, p1, section);
    int secKey2 = slotKey(day, p2, section);

    timetableSlots[section][day][p1].subjectId = -1;
    timetableSlots[section][day][p2].subjectId = -1;
    timetableSlots[section][day][p1].isLabPart = 0;
    timetableSlots[section][day][p2].isLabPart = 0;

    if (teacherAtTime[timeKey1] == labInfo->teacherId)
        teacherAtTime[timeKey1] = -1;
    if (teacherAtTime[timeKey2] == labInfo->teacherId)
        teacherAtTime[timeKey2] = -1;

    sectionBusy[secKey1] = 0;
    sectionBusy[secKey2] = 0;
    usedLabBlocks[labInfo->subjectId]--;
}

/* ---------- DFS for labs then lectures ---------- */

int dfsLab(int labIndex) {
    int day, period, sec;

    if (labIndex == labCount) return 1;

    for (day = 0; day < DAYS; ++day) {
        for (period = 0; period < PERIODS - 1; ++period) {
            sec = labs[labIndex].sectionId;
            if (canPlaceLabBlock(&labs[labIndex], day, period, sec)) {
                placeLabBlock(&labs[labIndex], day, period, sec);
                if (dfsLab(labIndex + 1)) return 1;
                removeLabBlock(&labs[labIndex], day, period, sec);
            }
        }
    }
    return 0;
}

int dfsLecture(int flatIndex) {
    int totalSlots = SECTIONS * DAYS * PERIODS;
    int section, rem, day, period;
    int i;

    if (flatIndex == totalSlots) return 1;

    section = flatIndex / (DAYS * PERIODS);
    rem = flatIndex % (DAYS * PERIODS);
    day = rem / PERIODS;
    period = rem % PERIODS;

    if (timetableSlots[section][day][period].subjectId != -1) {
        return dfsLecture(flatIndex + 1);
    }

    for (i = 0; i < subjectCount; ++i) {
        Subject *sub = &subjects[i];
        if (canPlaceLecture(sub, day, period, section)) {
            placeLecture(sub, day, period, section);
            if (dfsLecture(flatIndex + 1)) return 1;
            removeLecture(sub, day, period, section);
        }
    }

    /* Allow FREE slot if no subject fits */
    return dfsLecture(flatIndex + 1);
}

/* ---------- Printing ---------- */

void printTimetable() {
    int s, d, p;
    const char *dayNames[7] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

    printf("\n================ GENERATED TIMETABLE ================\n\n");
    for (s = 0; s < SECTIONS; ++s) {
        printf("Section: %s\n", sectionNames[s]);
        printf("Day\\Per\t");
        for (p = 0; p < PERIODS; ++p) {
            printf("P%d\t", p + 1);
        }
        printf("\n");
        for (d = 0; d < DAYS; ++d) {
            printf("%s\t", dayNames[d]);
            for (p = 0; p < PERIODS; ++p) {
                int sid = timetableSlots[s][d][p].subjectId;
                if (sid == -1) {
                    printf("FREE\t");
                } else {
                    Subject *sub = getSubjectById(sid);
                    if (sub != NULL) {
                        if (timetableSlots[s][d][p].isLabPart)
                            printf("%s_L\t", sub->name);
                        else
                            printf("%s\t", sub->name);
                    } else {
                        printf("S%d\t", sid);
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

/* ---------- Input helper to build a flexible dataset ---------- */

void readConfigFromUser() {
    int i, j;

    printf("Enter number of sections (<= %d): ", MAX_SECTIONS);
    scanf("%d", &SECTIONS);

    printf("Enter number of days (<= %d): ", MAX_DAYS);
    scanf("%d", &DAYS);

    printf("Enter number of periods per day (<= %d): ", MAX_PERIODS);
    scanf("%d", &PERIODS);

    for (i = 0; i < SECTIONS; ++i) {
        printf("Enter name for section %d: ", i);
        scanf("%s", sectionNames[i]);
    }

    printf("\nEnter total number of subjects (all sections combined) (<= %d): ",
           MAX_SUBJECTS);
    scanf("%d", &subjectCount);

    for (i = 0; i < subjectCount; ++i) {
        Subject s;
        s.id = i;
        printf("\n--- Subject %d ---\n", i);
        printf("Name (e.g., DSA): ");
        scanf("%s", s.name);
        printf("Teacher ID (int): ");
        scanf("%d", &s.teacherId);
        printf("Section ID (0..%d): ", SECTIONS - 1);
        scanf("%d", &s.sectionId);
        printf("Lectures per week: ");
        scanf("%d", &s.lecturesPerWeek);
        printf("Has 2-period lab? (1=yes, 0=no): ");
        scanf("%d", &s.hasLab);

        subjects[i] = s;
    }

    labCount = 0;
    for (i = 0; i < subjectCount && labCount < MAX_LABS; ++i) {
        if (subjects[i].hasLab) {
            Lab lb;
            int sessions;
            printf("\nLab for subject %s (id=%d, section=%d)\n",
                   subjects[i].name, subjects[i].id, subjects[i].sectionId);
            printf("Teacher ID for lab (can be same or different): ");
            scanf("%d", &lb.teacherId);
            printf("Number of 2-period lab sessions per week: ");
            scanf("%d", &sessions);

            lb.subjectId = subjects[i].id;
            lb.sectionId = subjects[i].sectionId;
            lb.sessionsPerWeek = sessions;

            labs[labCount++] = lb;
        }
    }

    printf("\nConfiguration complete. Generating timetable...\n\n");
}

/* ---------- Main ---------- */

int main() {
    int i, j, k;

    readConfigFromUser(); /* user chooses 2 sections, 5 days, 6 periods, etc. */

    for (i = 0; i < SECTIONS; ++i) {
        for (j = 0; j < DAYS; ++j) {
            for (k = 0; k < PERIODS; ++k) {
                timetableSlots[i][j][k].subjectId = -1;
                timetableSlots[i][j][k].isLabPart = 0;
            }
        }
    }
    for (i = 0; i < DAYS * PERIODS; ++i) {
        teacherAtTime[i] = -1;
    }
    for (i = 0; i < DAYS * PERIODS * SECTIONS; ++i) {
        sectionBusy[i] = 0;
    }
    for (i = 0; i < MAX_SUBJECTS; ++i) {
        usedLectures[i] = 0;
        usedLabBlocks[i] = 0;
    }

    if (!dfsLab(0)) {
        printf("Failed to place labs with given constraints.\n");
        return 0;
    }

    if (!dfsLecture(0)) {
        printf("Failed to place all lectures with given constraints.\n");
        return 0;
    }

    printTimetable();
    return 0;
}
