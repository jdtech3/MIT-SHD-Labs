from pathlib import Path


def main():
    out_path = Path("shared_file")
    with out_path.open(mode="wb"):
        out_path.write_bytes(bytearray([0] * 1024 * 128))


if __name__ == '__main__':
    main()
