#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <systemd/sd-journal.h>

int main(int argc, char *argv[]) {
    int subResult;
    int subErrno;
    int paramNum;
    struct iovec *pParams;
    int i;

    if (argc < 2) {
        fprintf(stderr, "usage: %s key1=value1 key2=value2 ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    paramNum = (argc - 1);

    pParams = calloc(paramNum, sizeof(struct iovec));
    if (!pParams) {
        subErrno = errno;
        fprintf(stderr, "calloc error. errno:%d message:%s paramNum:%d size:%zd\n",
                subErrno, strerror(subErrno), paramNum, sizeof(struct iovec));
        return EXIT_FAILURE;
    }

    for (i = 0; i < argc - 1; i++) {
        pParams[i].iov_base = argv[i + 1];
        pParams[i].iov_len = strlen(argv[i + 1]);
    }

    subResult = sd_journal_sendv(pParams, paramNum);
    if (subResult != 0) {
        subErrno = -subResult;
        fprintf(stderr, "sd_journal_sendv error. errno:%d message:%s\n",
                subErrno, strerror(subErrno));
        return EXIT_FAILURE;
    }

    free(pParams);

    return EXIT_SUCCESS;
}
